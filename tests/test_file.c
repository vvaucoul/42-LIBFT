/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
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

static int array_count(char **array)
{
	int i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		++i;
	return (i);
}

static int array_contains(char **array, const char *needle)
{
	int i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
	{
		if (strcmp(array[i], needle) == 0)
			return (1);
		++i;
	}
	return (0);
}

static void array_free(char **array)
{
	int i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
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

TEST(file, readline_long_line_survives_growth)
{
	char path[64];
	int fd;
	char *line;

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "abcdefghijklmnopqrstuvwxyz0123456789\n");
	fd = file_open(path, O_RDONLY, 0);
	line = file_readline(fd);
	ASSERT_NOT_NULL(line);
	ASSERT_EQ_STR(line, "abcdefghijklmnopqrstuvwxyz0123456789");
	free(line);
	file_close(fd);
	unlink(path);
}

TEST(file, readline_blank_line_returns_empty_string_not_null)
{
	char path[64];
	int fd;
	char *line;

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "first\n\nthird\n");
	fd = file_open(path, O_RDONLY, 0);

	line = file_readline(fd);
	ASSERT_EQ_STR(line, "first");
	free(line);

	line = file_readline(fd);
	ASSERT_NOT_NULL(line);
	ASSERT_EQ_STR(line, "");
	free(line);

	line = file_readline(fd);
	ASSERT_EQ_STR(line, "third");
	free(line);

	file_close(fd);
	unlink(path);
}

TEST(file, readline_true_eof_still_returns_null)
{
	char path[64];
	int fd;
	char *line;

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "only\n");
	fd = file_open(path, O_RDONLY, 0);

	line = file_readline(fd);
	ASSERT_EQ_STR(line, "only");
	free(line);

	ASSERT_NULL(file_readline(fd));
	file_close(fd);
	unlink(path);
}

TEST(file, readline_last_line_without_trailing_newline)
{
	char path[64];
	int fd;
	char *line;

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "no newline at all");
	fd = file_open(path, O_RDONLY, 0);

	line = file_readline(fd);
	ASSERT_EQ_STR(line, "no newline at all");
	free(line);

	ASSERT_NULL(file_readline(fd));
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

TEST(file, readall_returns_full_file_content)
{
	char path[64];
	char *content;

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "line one\nline two\n");
	content = file_readall(path);
	ASSERT_NOT_NULL(content);
	ASSERT_EQ_STR(content, "line one\nline two\n");
	free(content);
	unlink(path);
}

TEST(file, readall_preserves_blank_lines)
{
	char path[64];
	char *content;

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "a\n\nb\n");
	content = file_readall(path);
	ASSERT_NOT_NULL(content);
	ASSERT_EQ_STR(content, "a\n\nb\n");
	free(content);
	unlink(path);
}

TEST(file, readall_empty_file_returns_null)
{
	char path[64];

	tmp_path(path, sizeof(path), ".txt");
	write_raw_file(path, "");
	ASSERT_NULL(file_readall(path));
	unlink(path);
}

TEST(file, copy_preserves_blank_lines)
{
	char src[64];
	char dst[64];
	char *content;

	tmp_path(src, sizeof(src), "_src.txt");
	tmp_path(dst, sizeof(dst), "_dst.txt");
	write_raw_file(src, "a\n\nb\nc\n");
	file_copy(src, dst);
	content = file_readall(dst);
	ASSERT_NOT_NULL(content);
	ASSERT_EQ_STR(content, "a\n\nb\nc\n");
	free(content);
	unlink(src);
	unlink(dst);
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

TEST(file, dir_list_returns_single_entry)
{
	char dir_path[64];
	char file_path[80];
	char **entries;

	tmp_path(dir_path, sizeof(dir_path), "_dir2");
	rmdir(dir_path);
	mkdir(dir_path, 0755);
	snprintf(file_path, sizeof(file_path), "%s/a.txt", dir_path);
	write_raw_file(file_path, "x");

	entries = dir_list(dir_path);
	ASSERT_NOT_NULL(entries);
	ASSERT_EQ_INT(array_count(entries), 1);
	ASSERT(array_contains(entries, "a.txt"));
	array_free(entries);

	unlink(file_path);
	rmdir(dir_path);
}

TEST(file, dir_list_returns_every_entry_excluding_dot_and_dotdot)
{
	char dir_path[64];
	char file_a[80];
	char file_b[80];
	char **entries;

	tmp_path(dir_path, sizeof(dir_path), "_dir3");
	rmdir(dir_path);
	mkdir(dir_path, 0755);
	snprintf(file_a, sizeof(file_a), "%s/a.txt", dir_path);
	snprintf(file_b, sizeof(file_b), "%s/b.txt", dir_path);
	write_raw_file(file_a, "x");
	write_raw_file(file_b, "y");

	entries = dir_list(dir_path);
	ASSERT_NOT_NULL(entries);
	ASSERT_EQ_INT(array_count(entries), 2);
	ASSERT(array_contains(entries, "a.txt"));
	ASSERT(array_contains(entries, "b.txt"));
	ASSERT(!array_contains(entries, "."));
	ASSERT(!array_contains(entries, ".."));
	array_free(entries);

	unlink(file_a);
	unlink(file_b);
	rmdir(dir_path);
}

TEST(file, dir_list_recursive_empty_directory_returns_null)
{
	char path[64];
	char **entries;

	tmp_path(path, sizeof(path), "_rdir_empty");
	rmdir(path);
	mkdir(path, 0755);
	entries = dir_list_recursive(path);
	ASSERT_NULL(entries);
	rmdir(path);
}

TEST(file, dir_list_recursive_finds_nested_file)
{
	char dir_path[64];
	char sub_path[96];
	char top_file[96];
	char nested_file[128];
	char **entries;

	tmp_path(dir_path, sizeof(dir_path), "_rdir");
	rmdir(dir_path);
	mkdir(dir_path, 0755);
	snprintf(sub_path, sizeof(sub_path), "%s/sub", dir_path);
	mkdir(sub_path, 0755);
	snprintf(top_file, sizeof(top_file), "%s/top.txt", dir_path);
	snprintf(nested_file, sizeof(nested_file), "%s/nested.txt", sub_path);
	write_raw_file(top_file, "x");
	write_raw_file(nested_file, "y");

	entries = dir_list_recursive(dir_path);
	ASSERT_NOT_NULL(entries);
	ASSERT(array_contains(entries, "top.txt"));
	ASSERT(array_contains(entries, "sub"));
	ASSERT(array_contains(entries, "sub/nested.txt"));
	array_free(entries);

	unlink(nested_file);
	unlink(top_file);
	rmdir(sub_path);
	rmdir(dir_path);
}
