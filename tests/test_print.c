/* ************************************************************************** */
/*   test_print.c - srcs/print/ *.c (all write directly to fd 1)             */
/*                                                                            */
/*   Uses test_capture_fd1() to redirect fd 1 to a tmpfile for the duration  */
/*   of the call under test, then compares what was actually written.       */
/* ************************************************************************** */

#include <libft.h>
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

/* ft_putnbr(INT_MIN) does `ft_putnbr(nbr *= -1)` - negating INT_MIN
** overflows a 32-bit int (UB). In practice this commonly yields INT_MIN
** right back, so the "negative" branch recurses on the same value forever
** -> unbounded recursion -> stack overflow. Isolated in its own test so a
** crash here only costs this one line. */
TEST(print, putnbr_int_min_known_bug_isolated)
{
	g_int_arg = -2147483648;
	free(test_capture_fd1(action_putnbr));
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
