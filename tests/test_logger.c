/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_logger.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <logger.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
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

static int count_open_fds(void)
{
	DIR *d = opendir("/proc/self/fd");
	struct dirent *e;
	int count;

	if (!d)
		return (-1);
	count = 0;
	while ((e = readdir(d)))
		if (e->d_name[0] != '.')
			++count;
	closedir(d);
	return (count);
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

/* logger_fatal() is just a log-level label, it does not abort()/exit() despite the name. */
TEST(logger, fatal_does_not_terminate_process)
{
	char path[64];

	log_path(path, sizeof(path));
	logger_init(path);
	logger_fatal("this should not kill the test");
	logger_close();
	unlink(path);
}

TEST(logger, reinit_without_close_does_not_leak_fds)
{
	char path[64];
	int before;
	int after;
	int i;

	log_path(path, sizeof(path));
	before = count_open_fds();
	i = 0;
	while (i < 50)
	{
		logger_init(path);
		++i;
	}
	after = count_open_fds();
	logger_close();
	unlink(path);
	ASSERT_MSG(after - before <= 2,
		"logger_init() leaked file descriptors: %d open before, %d after "
		"50 re-inits", before, after);
}

TEST(logger, log_is_flushed_without_close)
{
	char path[64];
	char *content;

	log_path(path, sizeof(path));
	logger_init(path);
	logger_set_level(LOG_LEVEL_INFO);
	logger_info("flushed message");
	content = read_whole_file(path);
	ASSERT_NOT_NULL(content);
	ASSERT_NOT_NULL(strstr(content, "flushed message"));
	free(content);
	logger_close();
	unlink(path);
}

TEST(logger, logf_formats_message_with_arguments)
{
	char path[64];
	char *content;

	log_path(path, sizeof(path));
	logger_init(path);
	logger_set_level(LOG_LEVEL_INFO);
	logger_logf(LOG_LEVEL_INFO, "count=%d name=%s", 42, "test");
	logger_close();

	content = read_whole_file(path);
	ASSERT_NOT_NULL(content);
	ASSERT_NOT_NULL(strstr(content, "[INFO]"));
	ASSERT_NOT_NULL(strstr(content, "count=42 name=test"));
	free(content);
	unlink(path);
}

TEST(logger, logf_respects_level_filter)
{
	char path[64];
	char *content;

	log_path(path, sizeof(path));
	logger_init(path);
	logger_set_level(LOG_LEVEL_ERROR);
	logger_logf(LOG_LEVEL_DEBUG, "hidden %d", 1);
	logger_logf(LOG_LEVEL_ERROR, "shown %d", 2);
	logger_close();

	content = read_whole_file(path);
	ASSERT_NOT_NULL(content);
	ASSERT(strstr(content, "hidden") == NULL);
	ASSERT_NOT_NULL(strstr(content, "shown 2"));
	free(content);
	unlink(path);
}

TEST(logger, logf_before_init_is_a_safe_noop)
{
	logger_logf(LOG_LEVEL_INFO, "nobody is listening, count=%d", 1);
}

TEST(logger, get_level_reflects_set_level)
{
	ASSERT_EQ_INT(logger_get_level(), LOG_LEVEL_INFO);
	logger_set_level(LOG_LEVEL_ERROR);
	ASSERT_EQ_INT(logger_get_level(), LOG_LEVEL_ERROR);
}

TEST(logger, is_open_reflects_init_and_close)
{
	char path[64];

	ASSERT(!logger_is_open());
	log_path(path, sizeof(path));
	logger_init(path);
	ASSERT(logger_is_open());
	logger_close();
	ASSERT(!logger_is_open());
	unlink(path);
}
