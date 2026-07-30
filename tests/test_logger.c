/* ************************************************************************** */
/*   test_logger.c - srcs/logger/logger.c                                    */
/*                                                                            */
/*   logger_log() writes to a FILE* only (never stdout/stderr), so we read   */
/*   the log file back with plain libc I/O to check what was written.        */
/*   logger_init() on an unwritable path calls exit(EXIT_FAILURE) instead    */
/*   of returning an error - each test already runs in its own forked       */
/*   child (see test_framework.h), so that is exercised directly and just   */
/*   shows up as a documented non-zero exit rather than a crash.            */
/* ************************************************************************** */

#include <libft.h>
#include <logger.h>
#include <stdio.h>
#include <unistd.h>
#include "framework/test_framework.h"

static void log_path(char *buf, size_t n)
{
	snprintf(buf, n, "/tmp/libft_test_logger_%d.log", getpid());
}

static char *read_whole_file(const char *path)
{
	FILE *f = fopen(path, "r");
	char *buf;
	long len;

	if (!f)
		return (NULL);
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	rewind(f);
	buf = malloc(len + 1);
	fread(buf, 1, len, f);
	buf[len] = '\0';
	fclose(f);
	return (buf);
}

TEST(logger, filters_below_current_level)
{
	char path[64];
	char *content;

	log_path(path, sizeof(path));
	logger_init(path);
	logger_set_level(LOG_LEVEL_WARN);
	logger_debug("should not appear");
	logger_warn("should appear");
	logger_close();

	content = read_whole_file(path);
	ASSERT_NOT_NULL(content);
	ASSERT(strstr(content, "should not appear") == NULL);
	ASSERT_NOT_NULL(strstr(content, "should appear"));
	free(content);
	unlink(path);
}

TEST(logger, message_at_current_level_is_kept)
{
	char path[64];
	char *content;

	log_path(path, sizeof(path));
	logger_init(path);
	logger_set_level(LOG_LEVEL_INFO);
	logger_info("info line");
	logger_close();

	content = read_whole_file(path);
	ASSERT_NOT_NULL(content);
	ASSERT_NOT_NULL(strstr(content, "[INFO]"));
	ASSERT_NOT_NULL(strstr(content, "info line"));
	free(content);
	unlink(path);
}

TEST(logger, log_before_init_is_a_safe_noop)
{
	logger_debug("nobody is listening yet");
	logger_info("still nobody");
}

TEST(logger, close_is_safe_to_call_twice)
{
	char path[64];

	log_path(path, sizeof(path));
	logger_init(path);
	logger_close();
	logger_close();
	unlink(path);
}

/* logger_fatal() is just a log-level LABEL - it does not abort()/exit()
** the process despite the name. */
TEST(logger, fatal_does_not_terminate_process)
{
	char path[64];

	log_path(path, sizeof(path));
	logger_init(path);
	logger_fatal("this should not kill the test");
	logger_close();
	unlink(path);
}
