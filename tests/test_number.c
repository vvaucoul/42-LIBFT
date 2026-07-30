/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include "framework/test_framework.h"

TEST(number, nbrlen_basic)
{
	ASSERT_EQ_UINT(ft_nbrlen(0), 1);
	ASSERT_EQ_UINT(ft_nbrlen(1), 1);
	ASSERT_EQ_UINT(ft_nbrlen(9), 1);
	ASSERT_EQ_UINT(ft_nbrlen(10), 2);
	ASSERT_EQ_UINT(ft_nbrlen(99), 2);
	ASSERT_EQ_UINT(ft_nbrlen(100), 3);
	ASSERT_EQ_UINT(ft_nbrlen(2147483647), 10);
}

/* Integer division truncates toward zero the same way for both signs, so ft_nbrlen never adds 1 for a minus sign. */
TEST(number, nbrlen_negative_excludes_sign)
{
	ASSERT_EQ_UINT(ft_nbrlen(-5), 1);
	ASSERT_EQ_UINT(ft_nbrlen(-123456), 6);
}

TEST(number, nbrlen_int_min)
{
	ASSERT_EQ_UINT(ft_nbrlen(INT_MIN), 10);
}

TEST(number, nbrlen_long_basic)
{
	ASSERT_EQ_UINT(ft_nbrlen_long(0), 1);
	ASSERT_EQ_UINT(ft_nbrlen_long(100), 3);
	ASSERT_EQ_UINT(ft_nbrlen_long(-100), 3);
	/* LONG_MIN's magnitude is LONG_MAX + 1, but both are 19-digit numbers. */
	ASSERT_EQ_UINT(ft_nbrlen_long(LONG_MIN), ft_nbrlen_long(LONG_MAX));
}

TEST(number, nbrlen_llong_basic)
{
	ASSERT_EQ_UINT(ft_nbrlen_llong(0), 1);
	ASSERT_EQ_UINT(ft_nbrlen_llong(9223372036854775807LL), 19);
	ASSERT_EQ_UINT(ft_nbrlen_llong(-9223372036854775807LL - 1), 19);
}

TEST(number, nbrlen_base_basic)
{
	ASSERT_EQ_UINT(ft_nbrlen_base(0, 2), 1);
	ASSERT_EQ_UINT(ft_nbrlen_base(255, 16), 2);
	ASSERT_EQ_UINT(ft_nbrlen_base(255, 2), 8);
	ASSERT_EQ_UINT(ft_nbrlen_base(8, 8), 2);
}

TEST(number, nbrlen_base_excludes_sign)
{
	ASSERT_EQ_UINT(ft_nbrlen_base(-255, 16), 2);
}

TEST(number, nbrlen_base_int_min_every_base)
{
	ASSERT_EQ_UINT(ft_nbrlen_base(INT_MIN, 10), 10);
	ASSERT_EQ_UINT(ft_nbrlen_base(INT_MIN, 16), 8);
}

TEST(number, nbrlen_base_invalid_base_returns_zero)
{
	ASSERT_EQ_UINT(ft_nbrlen_base(10, 1), 0);
	ASSERT_EQ_UINT(ft_nbrlen_base(10, 17), 0);
}

TEST(number, abs_basic)
{
	ASSERT_EQ_INT(ft_abs(5), 5);
	ASSERT_EQ_INT(ft_abs(-5), 5);
	ASSERT_EQ_INT(ft_abs(0), 0);
}

TEST(number, abs_int_min_does_not_overflow)
{
	ASSERT_EQ_INT(ft_abs(INT_MIN), 2147483648L);
}

TEST(number, min_int_basic)
{
	ASSERT_EQ_INT(ft_min_int(3, 7), 3);
	ASSERT_EQ_INT(ft_min_int(7, 3), 3);
	ASSERT_EQ_INT(ft_min_int(-2, 2), -2);
	ASSERT_EQ_INT(ft_min_int(4, 4), 4);
}

TEST(number, max_int_basic)
{
	ASSERT_EQ_INT(ft_max_int(3, 7), 7);
	ASSERT_EQ_INT(ft_max_int(7, 3), 7);
	ASSERT_EQ_INT(ft_max_int(-2, 2), 2);
	ASSERT_EQ_INT(ft_max_int(4, 4), 4);
}

TEST(number, clamp_int_within_range_is_unchanged)
{
	ASSERT_EQ_INT(ft_clamp_int(5, 0, 10), 5);
}

TEST(number, clamp_int_clamps_below_and_above)
{
	ASSERT_EQ_INT(ft_clamp_int(-5, 0, 10), 0);
	ASSERT_EQ_INT(ft_clamp_int(15, 0, 10), 10);
}

TEST(number, pow_basic)
{
	ASSERT_EQ_INT(ft_pow(2, 10), 1024);
	ASSERT_EQ_INT(ft_pow(5, 0), 1);
	ASSERT_EQ_INT(ft_pow(0, 5), 0);
	ASSERT_EQ_INT(ft_pow(-2, 3), -8);
	ASSERT_EQ_INT(ft_pow(-2, 2), 4);
}

TEST(number, pow_negative_exponent_returns_zero)
{
	ASSERT_EQ_INT(ft_pow(2, -3), 0);
}

TEST(number, gcd_basic)
{
	ASSERT_EQ_INT(ft_gcd(12, 18), 6);
	ASSERT_EQ_INT(ft_gcd(17, 5), 1);
	ASSERT_EQ_INT(ft_gcd(0, 5), 5);
	ASSERT_EQ_INT(ft_gcd(0, 0), 0);
}

TEST(number, gcd_ignores_sign)
{
	ASSERT_EQ_INT(ft_gcd(-12, 18), 6);
	ASSERT_EQ_INT(ft_gcd(-12, -18), 6);
}

TEST(number, gcd_int_min_does_not_crash)
{
	ASSERT_EQ_INT(ft_gcd(INT_MIN, 0), 2147483648u);
}

TEST(number, lcm_basic)
{
	ASSERT_EQ_INT(ft_lcm(4, 6), 12);
	ASSERT_EQ_INT(ft_lcm(21, 6), 42);
}

TEST(number, lcm_zero_operand_returns_zero)
{
	ASSERT_EQ_INT(ft_lcm(0, 5), 0);
	ASSERT_EQ_INT(ft_lcm(5, 0), 0);
}

TEST(number, lcm_ignores_sign)
{
	ASSERT_EQ_INT(ft_lcm(-4, 6), 12);
}

TEST(number, lcm_large_values_do_not_overflow)
{
	/* 46337 and 46349 are both prime, so their product (~2.15e9) already exceeds INT_MAX. */
	ASSERT_EQ_INT(ft_lcm(46337, 46349), 2147673613L);
}

TEST(number, is_prime_small_values)
{
	ASSERT(!ft_is_prime(0));
	ASSERT(!ft_is_prime(1));
	ASSERT(ft_is_prime(2));
	ASSERT(ft_is_prime(3));
	ASSERT(!ft_is_prime(4));
	ASSERT(ft_is_prime(17));
	ASSERT(!ft_is_prime(21));
}

TEST(number, is_prime_negative_is_never_prime)
{
	ASSERT(!ft_is_prime(-7));
}

/* 2147483647 (INT_MAX) is a known Mersenne prime, exercising the loop bound near sqrt(INT_MAX). */
TEST(number, is_prime_int_max_is_prime)
{
	ASSERT(ft_is_prime(2147483647));
}

TEST(number, is_prime_large_composite_near_int_max)
{
	ASSERT(!ft_is_prime(2147483645));
}
