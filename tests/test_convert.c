/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
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

TEST(convert, itoa_int_min)
{
	char *s;

	s = ft_itoa(-2147483648);
	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "-2147483648");
	free(s);
}

TEST(convert, itoa_base_binary)
{
	char *s;

	s = ft_itoa_base(0, 2);
	ASSERT_EQ_STR(s, "0");
	free(s);

	s = ft_itoa_base(5, 2);
	ASSERT_EQ_STR(s, "101");
	free(s);

	s = ft_itoa_base(255, 2);
	ASSERT_EQ_STR(s, "11111111");
	free(s);
}

TEST(convert, itoa_base_octal_decimal_hex)
{
	char *s;

	s = ft_itoa_base(8, 8);
	ASSERT_EQ_STR(s, "10");
	free(s);

	s = ft_itoa_base(42, 10);
	ASSERT_EQ_STR(s, "42");
	free(s);

	s = ft_itoa_base(255, 16);
	ASSERT_EQ_STR(s, "ff");
	free(s);

	s = ft_itoa_base(4096, 16);
	ASSERT_EQ_STR(s, "1000");
	free(s);
}

TEST(convert, itoa_base_invalid_base_returns_null)
{
	ASSERT_NULL(ft_itoa_base(10, 1));
	ASSERT_NULL(ft_itoa_base(10, 0));
	ASSERT_NULL(ft_itoa_base(10, 17));
	ASSERT_NULL(ft_itoa_base(10, -5));
}

TEST(convert, itoa_base_negative_uses_sign_and_magnitude)
{
	char *s;

	s = ft_itoa_base(-1, 16);
	ASSERT_EQ_STR(s, "-1");
	free(s);

	s = ft_itoa_base(-5, 2);
	ASSERT_EQ_STR(s, "-101");
	free(s);

	s = ft_itoa_base(-255, 16);
	ASSERT_EQ_STR(s, "-ff");
	free(s);
}

TEST(convert, itoa_base_int_min_every_base)
{
	char *s;

	s = ft_itoa_base(-2147483648, 10);
	ASSERT_EQ_STR(s, "-2147483648");
	free(s);

	s = ft_itoa_base(-2147483648, 16);
	ASSERT_EQ_STR(s, "-80000000");
	free(s);
}

TEST(convert, atoi_base_round_trips_with_itoa_base)
{
	ASSERT_EQ_INT(ft_atoi_base("101", 2), 5);
	ASSERT_EQ_INT(ft_atoi_base("ff", 16), 255);
	ASSERT_EQ_INT(ft_atoi_base("-2a", 16), -42);
	ASSERT_EQ_INT(ft_atoi_base("777", 8), 511);
}

TEST(convert, atoi_base_invalid_base_returns_zero)
{
	ASSERT_EQ_INT(ft_atoi_base("101", 1), 0);
	ASSERT_EQ_INT(ft_atoi_base("101", 17), 0);
	ASSERT_EQ_INT(ft_atoi_base(NULL, 16), 0);
}

TEST(convert, atoi_base_stops_at_first_invalid_digit)
{
	ASSERT_EQ_INT(ft_atoi_base("1g", 16), 1);
	ASSERT_EQ_INT(ft_atoi_base("12", 2), 1);
}

TEST(convert, atol_basic)
{
	ASSERT_EQ_INT(ft_atol("42"), 42);
	ASSERT_EQ_INT(ft_atol("-42"), -42);
	ASSERT_EQ_INT(ft_atol("   +7"), 7);
	ASSERT_EQ_INT(ft_atol("abc"), 0);
}

TEST(convert, atoll_basic)
{
	ASSERT_EQ_INT(ft_atoll("42"), 42);
	ASSERT_EQ_INT(ft_atoll("-42"), -42);
	ASSERT_EQ_INT(ft_atoll("9223372036854775807"), 9223372036854775807LL);
}

TEST(convert, lltoa_basic)
{
	char *s;

	s = ft_lltoa(0);
	ASSERT_EQ_STR(s, "0");
	free(s);

	s = ft_lltoa(-42);
	ASSERT_EQ_STR(s, "-42");
	free(s);

	s = ft_lltoa(9223372036854775807LL);
	ASSERT_EQ_STR(s, "9223372036854775807");
	free(s);
}

TEST(convert, lltoa_llong_min)
{
	char *s = ft_lltoa(-9223372036854775807LL - 1);

	ASSERT_EQ_STR(s, "-9223372036854775808");
	free(s);
}

TEST(convert, lltoa_atoll_round_trip)
{
	char *s = ft_lltoa(123456789012345LL);

	ASSERT_EQ_INT(ft_atoll(s), 123456789012345LL);
	free(s);
}

TEST(convert, atof_integer_and_sign)
{
	ASSERT_EQ_DOUBLE(ft_atof("42"), 42.0, 0.0001);
	ASSERT_EQ_DOUBLE(ft_atof("-42"), -42.0, 0.0001);
	ASSERT_EQ_DOUBLE(ft_atof("+42"), 42.0, 0.0001);
}

TEST(convert, atof_fractional_part)
{
	ASSERT_EQ_DOUBLE(ft_atof("3.14"), 3.14, 0.0001);
	ASSERT_EQ_DOUBLE(ft_atof("-0.5"), -0.5, 0.0001);
	ASSERT_EQ_DOUBLE(ft_atof("0.001"), 0.001, 0.00001);
}

TEST(convert, atof_exponent_notation)
{
	ASSERT_EQ_DOUBLE(ft_atof("1e2"), 100.0, 0.0001);
	ASSERT_EQ_DOUBLE(ft_atof("1.5e-2"), 0.015, 0.0001);
	ASSERT_EQ_DOUBLE(ft_atof("2E3"), 2000.0, 0.0001);
}

TEST(convert, atof_null_returns_zero)
{
	ASSERT_EQ_DOUBLE(ft_atof(NULL), 0.0, 0.0001);
}
