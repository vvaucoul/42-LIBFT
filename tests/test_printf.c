/* ************************************************************************** */
/*   test_printf.c - srcs/printf/ft_printf.c and ft_sscanf.c                 */
/*                                                                            */
/*   ft_printf's inner dispatcher (display_case) only implements two         */
/*   conversions: %d/%i and %s. Every other conversion character (%u %x %X  */
/*   %o %p %c %% ...), and any flag/width/precision character, falls        */
/*   through as a silent no-op that also skips its va_arg() call - so it     */
/*   doesn't just "print nothing", it desyncs the va_list for every         */
/*   specifier that follows in the same call. ft_printf's return value is   */
/*   also hardcoded to 0 regardless of how many bytes were written.         */
/*   ft_sscanf is an entirely unimplemented stub that always returns 0 and  */
/*   never touches its format string or output pointers - it isn't         */
/*   declared in any header, so we declare our own prototype here.          */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

extern int ft_sscanf(const char *str, const char *format, ...);

static const char	*g_fmt;
static int			g_int_arg;
static const char	*g_str_arg;
static char			g_char_arg;
static int			g_ret;

static void action_d(void)
{
	g_ret = ft_printf(g_fmt, g_int_arg);
}

static void action_s(void)
{
	g_ret = ft_printf(g_fmt, g_str_arg);
}

static void action_cd(void)
{
	g_ret = ft_printf(g_fmt, g_char_arg, g_int_arg);
}

TEST(printf, d_and_i_print_normally)
{
	char *out;

	g_fmt = "%d";
	g_int_arg = 42;
	out = test_capture_fd1(action_d);
	ASSERT_EQ_STR(out, "42");
	free(out);

	g_fmt = "%i";
	g_int_arg = -7;
	out = test_capture_fd1(action_d);
	ASSERT_EQ_STR(out, "-7");
	free(out);
}

TEST(printf, s_prints_string)
{
	char *out;

	g_fmt = "%s";
	g_str_arg = "hello";
	out = test_capture_fd1(action_s);
	ASSERT_EQ_STR(out, "hello");
	free(out);
}

/* NULL is handled without crashing, but prints lowercase "null" - not
** glibc's "(null)". */
TEST(printf, s_null_prints_lowercase_null)
{
	char *out;

	g_fmt = "%s";
	g_str_arg = NULL;
	out = test_capture_fd1(action_s);
	ASSERT_EQ_STR(out, "null");
	free(out);
}

/* Return value is hardcoded to 0 in ft_printf's own success path,
** regardless of how many bytes were actually written. */
TEST(printf, return_value_is_always_zero_known_bug)
{
	g_fmt = "%s";
	g_str_arg = "some non-empty output";
	free(test_capture_fd1(action_s));
	ASSERT_MSG(g_ret == (int)strlen("some non-empty output"),
		"ft_printf should return the number of bytes written (%zu), but "
		"always returns %d", strlen("some non-empty output"), g_ret);
}

/* %c is entirely unimplemented: it neither prints the char nor consumes
** its va_arg. The following %d then reads THAT unconsumed argument
** instead of its own - every conversion other than %d/%i/%s corrupts the
** rest of the va_list for the call. */
TEST(printf, unsupported_conversions_desync_va_list_known_bug)
{
	char *out;

	g_fmt = "%c%d";
	g_char_arg = 'A';
	g_int_arg = 99;
	out = test_capture_fd1(action_cd);
	ASSERT_MSG(!strcmp(out, "A99"),
		"ft_printf(\"%%c%%d\", 'A', 99) should print \"A99\", got \"%s\" "
		"(%%c is a no-op that never calls va_arg, so %%d reads the char "
		"argument instead of the int one)", out);
	free(out);
}

/* %% is one of the unsupported conversions too: it doesn't even fall back
** to printing a literal '%' - the pair of characters just produces
** nothing at all. */
static void action_literal_percent(void)
{
	g_ret = ft_printf("100%%");
}

TEST(printf, percent_percent_prints_nothing_known_bug)
{
	char *out;

	out = test_capture_fd1(action_literal_percent);
	ASSERT_MSG(!strcmp(out, "100%"),
		"ft_printf(\"100%%%%\") should print \"100%%\", got \"%s\" (%%%% "
		"falls into the same unimplemented-conversion no-op as every "
		"other unsupported specifier)", out);
	free(out);
}

static void action_trailing_percent(void)
{
	g_ret = ft_printf("abc%");
}

/* A '%' as the very last byte of the format string makes the parser look
** at str[i+1] == '\0' (safe), but then advance by 2 regardless, landing
** one byte past the NUL terminator for the next loop-condition check -
** an out-of-bounds read. Isolated since the outcome depends on what
** happens to sit in the byte after the string's allocation. */
TEST(printf, trailing_percent_oob_read_known_bug_isolated)
{
	char *out = test_capture_fd1(action_trailing_percent);

	ASSERT_MSG(!strncmp(out, "abc", 3),
		"ft_printf(\"abc%%\") should at least print \"abc\" before hitting "
		"the trailing %%, got \"%s\"", out);
	free(out);
}

static void action_int_min(void)
{
	g_ret = ft_printf("%d", -2147483648);
}

/* ft_putnbr(INT_MIN) negates INT_MIN (`nbr *= -1`), which overflows a
** 32-bit int (UB) and in practice commonly yields INT_MIN right back,
** causing unbounded recursion -> stack overflow. Isolated. */
TEST(printf, d_int_min_known_bug_isolated)
{
	free(test_capture_fd1(action_int_min));
}

TEST(sscanf, always_returns_zero_and_never_writes_known_bug)
{
	int target = -999999;
	int ret = ft_sscanf("42", "%d", &target);

	ASSERT_EQ_INT(ret, 0);
	ASSERT_MSG(target == -999999,
		"ft_sscanf(\"42\", \"%%d\", &target) is a stub: target should "
		"remain untouched at the sentinel value (got %d) and it does, "
		"but it should really have parsed 42", target);
}

TEST(sscanf, null_arguments_do_not_crash)
{
	ASSERT_EQ_INT(ft_sscanf(NULL, NULL), 0);
}
