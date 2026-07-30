/* ************************************************************************** */
/*   test_file.c - srcs/file/file.c                                          */
/*                                                                            */
/*   Most failure paths here (bad fd, missing file/dir...) call              */
/*   exit(EXIT_FAILURE) instead of returning an error code - not exercised   */
/*   below since there is nothing to assert on afterward (the process is    */
/*   already gone). Every test uses real temp files/dirs under /tmp, keyed  */
/*   by getpid() for isolation, and cleans up after itself with plain libc  */
/*   calls (not file_delete/dir_delete, since misuse there would just       */
/*   exit(1) the test process rather than reporting a clean failure).       */
/* ************************************************************************** */

#include <libft.h>
#include <file.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "framework/test_framework.h"

static void tmp_path(char *buf, size_t n, const char *suffix)
{
	snprintf(buf, n, "/tmp/libft_test_file_%d%s", getpid(), suffix);
}

static void write_raw_file(const char *path, const char *content)
{
	int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	write(fd, content, strlen(content));
	close(fd);
}

TEST(file, exists_true_and_false)
{
	char path[64];

	tmp_path(path, sizeof(path), ".txt");
	unlink(path);
	ASSERT(!file_exists(path));
	write_raw_file(path, "x");
	ASSERT(file_exists(path));
	unlink(path);
}

TEST(file, size_matches_content_length)
{
	char path[64];

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "hello world");
	ASSERT_EQ_INT(file_size(path), 11);
	unlink(path);
}

TEST(file, readline_short_line_works)
{
	char path[64];
	int fd;
	char *line;

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "hi\nthere\n");
	fd = file_open(path, O_RDONLY, 0);
	line = file_readline(fd);
	ASSERT_NOT_NULL(line);
	ASSERT_EQ_STR(line, "hi");
	free(line);
	file_close(fd);
	unlink(path);
}

/* file_readline grows its buffer via ft_realloc(line, (i+1)*1). Because
** ft_realloc treats the old block's size as a hardcoded sizeof(ptr) == 8,
** any grow request for newsize <= 8 just returns the SAME (too-small)
** pointer without actually resizing it - so characters at index 1..7 are
** written past the true 1-byte allocation (masked in practice by glibc's
** malloc minimum chunk size). Once a real regrow finally happens past
** byte 8, it only ever memcpy's the first 8 bytes forward each time - so
** every byte from index 8 onward is permanently replaced with
** uninitialized heap garbage on the NEXT regrow, no matter how many more
** characters get appended afterward. */
TEST(file, readline_long_line_corrupts_past_8_bytes_known_bug)
{
	char path[64];
	int fd;
	char *line;

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "abcdefghijkl\n");
	fd = file_open(path, O_RDONLY, 0);
	line = file_readline(fd);
	ASSERT_NOT_NULL(line);
	ASSERT_MSG(!strncmp(line, "abcdefgh", 8),
		"the first 8 bytes should at least survive, got \"%.8s\"", line);
	ASSERT_MSG(!strcmp(line, "abcdefghijkl"),
		"file_readline should return \"abcdefghijkl\" but bytes past "
		"index 8 are corrupted by ft_realloc's 8-byte-only memcpy");
	free(line);
	file_close(fd);
	unlink(path);
}

/* An empty line reads zero bytes before the '\n', so `i` stays 0 and the
** function returns NULL - identical to true EOF. A caller looping
** `while ((l = file_readline(fd)))` cannot tell a blank line apart from
** "no more data" and will stop reading early. */
TEST(file, readline_blank_line_indistinguishable_from_eof_known_bug)
{
	char path[64];
	int fd;
	char *line;

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "first\n\nthird\n");
	fd = file_open(path, O_RDONLY, 0);

	line = file_readline(fd);
	ASSERT_NOT_NULL(line);
	ASSERT_EQ_STR(line, "first");
	free(line);

	line = file_readline(fd);
	ASSERT_MSG(line != NULL,
		"file_readline on a blank line should return \"\" (or otherwise "
		"be distinguishable from EOF), but it returns NULL just like EOF");

	file_close(fd);
	unlink(path);
}

TEST(file, writeline_does_not_append_newline)
{
	char path[64];
	int fd;
	char buf[16];
	int n;

	tmp_path(path, sizeof(path), ".txt");
	fd = file_open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	file_writeline(fd, "hello");
	file_close(fd);

	fd = open(path, O_RDONLY);
	n = read(fd, buf, sizeof(buf) - 1);
	buf[n] = '\0';
	close(fd);
	ASSERT_EQ_STR(buf, "hello");
	unlink(path);
}

/* file_readall accumulates into `line` via ft_strjoin(line, tmp), but
** ft_strjoin(str, join) returns NULL whenever str==NULL (it does not
** treat NULL as ""). `line` starts NULL and is reassigned from that same
** call every iteration, so it can never become non-NULL: file_readall
** always returns NULL, for any file, regardless of content. */
TEST(file, readall_always_returns_null_known_bug)
{
	char path[64];
	char *content;

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "line one\nline two\n");
	content = file_readall(path);
	ASSERT_MSG(content != NULL,
		"file_readall should return the file's content, but always "
		"returns NULL (ft_strjoin(NULL, tmp) short-circuits to NULL)");
	unlink(path);
}

TEST(file, dir_list_empty_directory_returns_null)
{
	char path[64];
	char **entries;

	tmp_path(path, sizeof(path), "_dir");
	rmdir(path);
	mkdir(path, 0755);
	entries = dir_list(path);
	ASSERT_NULL(entries);
	rmdir(path);
}

/* dir_list()/dir_lit_recursive() grow `filenames` via
** ft_realloc(filenames, (ft_arraylen(filenames) + 2) * sizeof(char *)),
** but `filenames` starts NULL and ft_arraylen() has no NULL guard
** (`while (array[i] != NULL)` dereferences array[0] unconditionally) - so
** the very first real directory entry crashes the call. Isolated. */
TEST(file, dir_list_directory_with_entry_known_bug_isolated)
{
	char dir_path[64];
	char file_path[80];

	tmp_path(dir_path, sizeof(dir_path), "_dir2");
	rmdir(dir_path);
	mkdir(dir_path, 0755);
	snprintf(file_path, sizeof(file_path), "%s/a.txt", dir_path);
	write_raw_file(file_path, "x");

	dir_list(dir_path);

	unlink(file_path);
	rmdir(dir_path);
}
