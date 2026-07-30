/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

static void burn_cpu(void)
{
	volatile long sum = 0;
	long i;

	i = 0;
	while (i < 20000000)
	{
		sum += i;
		++i;
	}
}

TEST(time, stop_timer_is_non_negative)
{
	clock_t start;
	double elapsed;

	ft_start_timer(&start);
	burn_cpu();
	elapsed = ft_stop_timer(start);
	ASSERT(elapsed >= 0.0);
}

TEST(time, independent_timers_do_not_interfere)
{
	clock_t start_a;
	clock_t start_b;

	ft_start_timer(&start_a);
	burn_cpu();
	ft_start_timer(&start_b);
	burn_cpu();
	ASSERT(ft_stop_timer(start_b) <= ft_stop_timer(start_a));
}

TEST(time, monotonic_ms_measures_elapsed_wall_clock_time)
{
	long long before;
	long long after;

	before = ft_monotonic_ms();
	ft_sleep_ms(20);
	after = ft_monotonic_ms();
	ASSERT(before >= 0);
	ASSERT(after >= before + 15);
}

TEST(time, monotonic_ms_is_nondecreasing)
{
	long long a;
	long long b;

	a = ft_monotonic_ms();
	burn_cpu();
	b = ft_monotonic_ms();
	ASSERT(b >= a);
}

/* Measured via wall-clock time, not CPU time, since a sleeping process burns no CPU. */
TEST(time, sleep_ms_blocks_for_approximately_the_requested_duration)
{
	long long before;
	long long elapsed;

	before = ft_monotonic_ms();
	ft_sleep_ms(30);
	elapsed = ft_monotonic_ms() - before;
	ASSERT(elapsed >= 25);
}

TEST(time, now_string_default_format_has_expected_shape)
{
	char buf[64];
	char *r;

	r = ft_now_string(buf, sizeof(buf), NULL);
	ASSERT_EQ_PTR(r, buf);
	ASSERT_EQ_INT((int)ft_strlen(buf), 19);
	ASSERT_EQ_INT(buf[4], '-');
	ASSERT_EQ_INT(buf[7], '-');
	ASSERT_EQ_INT(buf[10], ' ');
	ASSERT_EQ_INT(buf[13], ':');
	ASSERT_EQ_INT(buf[16], ':');
}

TEST(time, now_string_custom_format)
{
	char buf[16];

	ft_now_string(buf, sizeof(buf), "%Y");
	ASSERT_EQ_INT((int)ft_strlen(buf), 4);
}

TEST(time, now_string_null_buf_returns_null)
{
	ASSERT_NULL(ft_now_string(NULL, 10, NULL));
}

TEST(time, now_string_zero_size_returns_null)
{
	char buf[8];

	ASSERT_NULL(ft_now_string(buf, 0, NULL));
}
