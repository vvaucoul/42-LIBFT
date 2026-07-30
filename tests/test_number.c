/* ************************************************************************** */
/*   test_number.c - srcs/number/ft_nbrlen.c                                */
/* ************************************************************************** */

#include <libft.h>
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

/* Integer division truncates toward zero the same way for negative and
** positive operands, so the `nbr /= 10` loop counts the same number of
** digits either way - ft_nbrlen never adds 1 for a leading minus sign. */
TEST(number, nbrlen_negative_excludes_sign)
{
	ASSERT_EQ_UINT(ft_nbrlen(-5), 1);
	ASSERT_EQ_UINT(ft_nbrlen(-123456), 6);
}
