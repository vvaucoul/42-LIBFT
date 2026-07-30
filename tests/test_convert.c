/* ************************************************************************** */
/*   test_convert.c - srcs/convert/ *.c (ft_atoi, ft_itoa, ft_itoa_base)      */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(convert, atoi_basic)
{
	ASSERT_EQ_INT(ft_atoi("0"), 0);
	ASSERT_EQ_INT(ft_atoi("42"), 42);
	ASSERT_EQ_INT(ft_atoi("-42"), -42);
	ASSERT_EQ_INT(ft_atoi("+42"), 42);
	ASSERT_EQ_INT(ft_atoi("2147483647"), 2147483647);
}

TEST(convert, atoi_leading_whitespace)
{
	ASSERT_EQ_INT(ft_atoi("   42"), 42);
	ASSERT_EQ_INT(ft_atoi("\t\n\v\f\r 7"), 7);
	ASSERT_EQ_INT(ft_atoi("  -7"), -7);
}

TEST(convert, atoi_stops_at_first_non_digit)
{
	ASSERT_EQ_INT(ft_atoi("42abc"), 42);
	ASSERT_EQ_INT(ft_atoi("12.5"), 12);
	ASSERT_EQ_INT(ft_atoi("42 43"), 42);
}

TEST(convert, atoi_no_digits)
{
	ASSERT_EQ_INT(ft_atoi(""), 0);
	ASSERT_EQ_INT(ft_atoi("abc"), 0);
	ASSERT_EQ_INT(ft_atoi("-"), 0);
	ASSERT_EQ_INT(ft_atoi("+"), 0);
	ASSERT_EQ_INT(ft_atoi("   "), 0);
}

TEST(convert, itoa_basic)
{
	char *s;

	s = ft_itoa(0);
	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "0");
	free(s);

	s = ft_itoa(42);
	ASSERT_EQ_STR(s, "42");
	free(s);

	s = ft_itoa(-42);
	ASSERT_EQ_STR(s, "-42");
	free(s);

	s = ft_itoa(1);
	ASSERT_EQ_STR(s, "1");
	free(s);

	s = ft_itoa(-1);
	ASSERT_EQ_STR(s, "-1");
	free(s);
}

TEST(convert, itoa_int_max)
{
	char *s;

	s = ft_itoa(2147483647);
	ASSERT_EQ_STR(s, "2147483647");
	free(s);
}

/* ft_itoa(INT_MIN) special-cases via is_min_int(), which routes through the
** buggy ft_strdup (allocates strlen() bytes with no room for the NUL
** terminator). Kept as its own test so a crash/garbage read here doesn't
** take down the rest of the convert suite (fork isolation). */
TEST(convert, itoa_int_min_known_bug)
{
	char *s;

	s = ft_itoa(-2147483648);
	ASSERT_NOT_NULL(s);
	ASSERT_MSG(!strncmp(s, "-2147483648", 11),
		"ft_itoa(INT_MIN) should start with \"-2147483648\", got \"%.11s\"",
		s);
}

TEST(convert, itoa_base_binary)
{
	char *s;

	s = ft_itoa_base(0, 2);
	ASSERT_EQ_STR(s, "0");

	s = ft_itoa_base(5, 2);
	ASSERT_EQ_STR(s, "101");

	s = ft_itoa_base(255, 2);
	ASSERT_EQ_STR(s, "11111111");
}

TEST(convert, itoa_base_octal_decimal_hex)
{
	char *s;

	s = ft_itoa_base(8, 8);
	ASSERT_EQ_STR(s, "10");

	s = ft_itoa_base(42, 10);
	ASSERT_EQ_STR(s, "42");

	s = ft_itoa_base(255, 16);
	ASSERT_EQ_STR(s, "ff");

	s = ft_itoa_base(4096, 16);
	ASSERT_EQ_STR(s, "1000");
}

TEST(convert, itoa_base_invalid_base_returns_null)
{
	ASSERT_NULL(ft_itoa_base(10, 1));
	ASSERT_NULL(ft_itoa_base(10, 0));
	ASSERT_NULL(ft_itoa_base(10, 17));
	ASSERT_NULL(ft_itoa_base(10, -5));
}

/* Negative numbers in ft_itoa_base always go through ft_itoa_neg_base(),
** which ignores `base` entirely and hardcodes an 8-char two's-complement-like
** hex string built on top of a strdup("ffffffff") buffer that is 1 byte too
** small for its own NUL terminator - the result is never NUL-terminated.
** We only assert on the bytes that are documented to be written (the first
** 8), and never index/print past that to stay inside the (buggy) allocation. */
TEST(convert, itoa_base_negative_known_bug)
{
	char *s;

	s = ft_itoa_base(-1, 16);
	ASSERT_NOT_NULL(s);
	ASSERT_MSG(!strncmp(s, "ffffffff", 8),
		"ft_itoa_base(-1, 16): expected two's-complement \"ffffffff\" "
		"prefix, got \"%.8s\"", s);
}
