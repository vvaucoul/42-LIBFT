/* ************************************************************************** */
/*   test_time.c - srcs/time/speed.c (startTimer/stopTimer)                 */
/*                                                                            */
/*   Both functions thread all state through the caller's own `clock_t`     */
/*   variable - there is no global timer, so independent timers never       */
/*   interfere with each other. Note: this measures CPU time via clock(),   */
/*   not wall-clock time, so tests must burn CPU (not sleep()) to see any   */
/*   measurable elapsed time.                                                */
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

	startTimer(&start);
	burn_cpu();
	elapsed = stopTimer(start);
	ASSERT(elapsed >= 0.0);
}

TEST(time, independent_timers_do_not_interfere)
{
	clock_t start_a;
	clock_t start_b;

	startTimer(&start_a);
	burn_cpu();
	startTimer(&start_b);
	burn_cpu();
	ASSERT(stopTimer(start_b) <= stopTimer(start_a));
}
