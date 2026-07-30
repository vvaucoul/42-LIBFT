/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include "framework/test_framework.h"

static const char	*g_str_arg;
static int			g_int_arg;
static const char	**g_arr_arg;

static void action_putchar(void)
{
	ft_putchar((char)g_int_arg);
}

static void action_putstr(void)
{
	ft_putstr(g_str_arg);
}

static void action_putendl(void)
{
	ft_putendl(g_str_arg);
}

static void action_putnbr(void)
{
	ft_putnbr(g_int_arg);
}

static void action_putsarray(void)
{
	ft_putsarray(g_arr_arg);
}

TEST(print, putchar_writes_one_byte)
{
	char *out;

	g_int_arg = 'X';
	out = test_capture_fd1(action_putchar);
	ASSERT_NOT_NULL(out);
	ASSERT_EQ_STR(out, "X");
	free(out);
}

TEST(print, putstr_no_trailing_newline)
{
	char *out;

	g_str_arg = "hello";
	out = test_capture_fd1(action_putstr);
	ASSERT_EQ_STR(out, "hello");
	free(out);
}

TEST(print, putstr_empty_string)
{
	char *out;

	g_str_arg = "";
	out = test_capture_fd1(action_putstr);
	ASSERT_EQ_STR(out, "");
	free(out);
}

TEST(print, putendl_adds_trailing_newline)
{
	char *out;

	g_str_arg = "hello";
	out = test_capture_fd1(action_putendl);
	ASSERT_EQ_STR(out, "hello\n");
	free(out);
}

TEST(print, putnbr_positive_negative_zero)
{
	char *out;

	g_int_arg = 42;
	out = test_capture_fd1(action_putnbr);
	ASSERT_EQ_STR(out, "42");
	free(out);

	g_int_arg = -42;
	out = test_capture_fd1(action_putnbr);
	ASSERT_EQ_STR(out, "-42");
	free(out);

	g_int_arg = 0;
	out = test_capture_fd1(action_putnbr);
	ASSERT_EQ_STR(out, "0");
	free(out);
}

TEST(print, putnbr_int_max)
{
	char *out;

	g_int_arg = 2147483647;
	out = test_capture_fd1(action_putnbr);
	ASSERT_EQ_STR(out, "2147483647");
	free(out);
}

/* Negating INT_MIN overflows a 32-bit int (UB), so this is isolated here. */
TEST(print, putnbr_int_min_prints_correctly)
{
	char *out;

	g_int_arg = -2147483648;
	out = test_capture_fd1(action_putnbr);
	ASSERT_EQ_STR(out, "-2147483648");
	free(out);
}

TEST(print, putsarray_prints_each_with_newline)
{
	const char *arr[] = {"foo", "bar", "baz", NULL};
	char *out;

	g_arr_arg = arr;
	out = test_capture_fd1(action_putsarray);
	ASSERT_EQ_STR(out, "foo\nbar\nbaz\n");
	free(out);
}

TEST(print, putsarray_null_array_is_safe)
{
	char *out;

	g_arr_arg = NULL;
	out = test_capture_fd1(action_putsarray);
	ASSERT_EQ_STR(out, "");
	free(out);
}

static void action_putchar_fd(void)
{
	ft_putchar_fd((char)g_int_arg, 1);
}

static void action_putstr_fd(void)
{
	ft_putstr_fd(g_str_arg, 1);
}

static void action_putendl_fd(void)
{
	ft_putendl_fd(g_str_arg, 1);
}

static void action_putnbr_fd(void)
{
	ft_putnbr_fd(g_int_arg, 1);
}

static void action_putsarray_fd(void)
{
	ft_putsarray_fd(g_arr_arg, 1);
}

TEST(print, putchar_fd_matches_putchar)
{
	char *out;

	g_int_arg = 'Z';
	out = test_capture_fd1(action_putchar_fd);
	ASSERT_EQ_STR(out, "Z");
	free(out);
}

TEST(print, putstr_fd_matches_putstr)
{
	char *out;

	g_str_arg = "hello";
	out = test_capture_fd1(action_putstr_fd);
	ASSERT_EQ_STR(out, "hello");
	free(out);
}

TEST(print, putstr_fd_null_is_safe)
{
	char *out;

	g_str_arg = NULL;
	out = test_capture_fd1(action_putstr_fd);
	ASSERT_EQ_STR(out, "");
	free(out);
}

TEST(print, putendl_fd_matches_putendl)
{
	char *out;

	g_str_arg = "hello";
	out = test_capture_fd1(action_putendl_fd);
	ASSERT_EQ_STR(out, "hello\n");
	free(out);
}

TEST(print, putnbr_fd_matches_putnbr)
{
	char *out;

	g_int_arg = -42;
	out = test_capture_fd1(action_putnbr_fd);
	ASSERT_EQ_STR(out, "-42");
	free(out);
}

TEST(print, putnbr_fd_int_min_prints_correctly)
{
	char *out;

	g_int_arg = -2147483648;
	out = test_capture_fd1(action_putnbr_fd);
	ASSERT_EQ_STR(out, "-2147483648");
	free(out);
}

TEST(print, putsarray_fd_matches_putsarray)
{
	const char *arr[] = {"foo", "bar", NULL};
	char *out;

	g_arr_arg = arr;
	out = test_capture_fd1(action_putsarray_fd);
	ASSERT_EQ_STR(out, "foo\nbar\n");
	free(out);
}

/* Writes to a pipe and reads it back to confirm fd is honored, independent of fd 1. */
TEST(print, putstr_fd_writes_to_arbitrary_fd)
{
	int pipefd[2];
	char buf[16];
	ssize_t n;

	ASSERT(pipe(pipefd) == 0);
	ft_putstr_fd("hi", pipefd[1]);
	close(pipefd[1]);
	n = read(pipefd[0], buf, sizeof(buf) - 1);
	close(pipefd[0]);
	ASSERT(n >= 0);
	buf[n] = '\0';
	ASSERT_EQ_STR(buf, "hi");
}
