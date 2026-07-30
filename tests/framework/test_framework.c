/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_framework.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>

#define TEST_TIMEOUT_SECONDS 5
#define EXIT_ASSERT_FAIL 42

#define C_RESET  "\033[0m"
#define C_BOLD   "\033[1m"
#define C_DIM    "\033[2m"
#define C_RED    "\033[31m"
#define C_GREEN  "\033[32m"
#define C_YELLOW "\033[33m"
#define C_CYAN   "\033[36m"

typedef struct s_test_case
{
	const char	*suite;
	const char	*name;
	t_test_fn	fn;
}	t_test_case;

static t_test_case	*g_tests = NULL;
static size_t		g_count = 0;
static size_t		g_cap = 0;

void	test_register(const char *suite, const char *name, t_test_fn fn)
{
	if (g_count == g_cap)
	{
		g_cap = g_cap ? g_cap * 2 : 64;
		g_tests = realloc(g_tests, g_cap * sizeof(*g_tests));
		if (!g_tests)
		{
			perror("test_register: realloc");
			exit(EXIT_FAILURE);
		}
	}
	g_tests[g_count].suite = suite;
	g_tests[g_count].name = name;
	g_tests[g_count].fn = fn;
	++g_count;
}

void	t_fail(const char *file, int line, const char *fmt, ...)
{
	va_list	ap;

	printf(C_RED "FAIL" C_RESET "\n");
	printf("      " C_DIM "%s:%d:" C_RESET " ", file, line);
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	printf("\n");
	fflush(stdout);
	_exit(EXIT_ASSERT_FAIL);
}

char	*test_capture_fd1(void (*action)(void))
{
	int		saved_fd1;
	FILE	*tmp;
	long	len;
	char	*buf;
	ssize_t	n;

	fflush(stdout);
	saved_fd1 = dup(1);
	tmp = tmpfile();
	if (!tmp || saved_fd1 < 0)
		return (NULL);
	dup2(fileno(tmp), 1);
	action();
	fflush(stdout);
	len = ftell(tmp);
	if (len < 0)
		len = 0;
	buf = malloc((size_t)len + 1);
	if (buf)
	{
		rewind(tmp);
		n = read(fileno(tmp), buf, (size_t)len);
		if (n < 0)
			n = 0;
		buf[n] = '\0';
	}
	dup2(saved_fd1, 1);
	close(saved_fd1);
	fclose(tmp);
	return (buf);
}

static double	elapsed_seconds(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec)
		+ (end.tv_usec - start.tv_usec) / 1e6);
}

static void	run_one(t_test_case *test, size_t *passed, size_t *failed,
		size_t *crashed, size_t *timedout)
{
	pid_t	pid;
	int		status;

	printf("  %-52s", test->name);
	fflush(stdout);
	pid = fork();
	if (pid < 0)
	{
		printf(C_RED "FORK ERROR" C_RESET "\n");
		++(*failed);
		return ;
	}
	if (pid == 0)
	{
		alarm(TEST_TIMEOUT_SECONDS);
		test->fn();
		fflush(stdout);
		_exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		int code = WEXITSTATUS(status);
		if (code == 0)
		{
			printf(C_GREEN "OK" C_RESET "\n");
			++(*passed);
		}
		else if (code == EXIT_ASSERT_FAIL)
			++(*failed);
		else
		{
			printf(C_RED "FAIL" C_RESET " (exited %d)\n", code);
			++(*failed);
		}
	}
	else if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGALRM)
		{
			printf(C_YELLOW "TIMEOUT" C_RESET " (> %ds, likely infinite "
				"loop / OOB read)\n", TEST_TIMEOUT_SECONDS);
			++(*timedout);
		}
		else
		{
			printf(C_RED "CRASH" C_RESET " (%s)\n", strsignal(sig));
			++(*crashed);
		}
	}
}

int	test_run_all(int verbose)
{
	size_t		passed;
	size_t		failed;
	size_t		crashed;
	size_t		timedout;
	const char	**seen;
	size_t		seen_count;
	size_t		s;
	size_t		i;
	int			already;
	struct timeval	t0;
	struct timeval	t1;

	(void)verbose;
	passed = 0;
	failed = 0;
	crashed = 0;
	timedout = 0;
	seen = malloc(sizeof(char *) * (g_count ? g_count : 1));
	seen_count = 0;
	gettimeofday(&t0, NULL);
	s = 0;
	while (s < g_count)
	{
		already = 0;
		i = 0;
		while (i < seen_count)
		{
			if (strcmp(seen[i], g_tests[s].suite) == 0)
				already = 1;
			++i;
		}
		if (!already)
		{
			seen[seen_count++] = g_tests[s].suite;
			printf("\n" C_BOLD C_CYAN "%s" C_RESET "\n", g_tests[s].suite);
			i = 0;
			while (i < g_count)
			{
				if (strcmp(g_tests[i].suite, g_tests[s].suite) == 0)
					run_one(&g_tests[i], &passed, &failed, &crashed,
						&timedout);
				++i;
			}
		}
		++s;
	}
	gettimeofday(&t1, NULL);
	printf("\n" C_BOLD "────────────────────────────────────────────────────"
		C_RESET "\n");
	printf("  Total     : %zu\n", g_count);
	printf("  " C_GREEN "Passed    : %zu" C_RESET "\n", passed);
	if (failed)
		printf("  " C_RED "Failed    : %zu" C_RESET "\n", failed);
	if (crashed)
		printf("  " C_RED "Crashed   : %zu" C_RESET "\n", crashed);
	if (timedout)
		printf("  " C_YELLOW "Timeout   : %zu" C_RESET "\n", timedout);
	printf("  Duration  : %.3fs\n", elapsed_seconds(t0, t1));
	free(seen);
	return ((failed || crashed || timedout) ? 1 : 0);
}
