/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(pair, new_holds_both_values)
{
	int a = 1;
	int b = 2;
	Pair *p = pair_new(&a, &b);

	ASSERT_NOT_NULL(p);
	ASSERT_EQ_PTR(pair_first(p), &a);
	ASSERT_EQ_PTR(pair_second(p), &b);
	pair_delete(p);
}

TEST(pair, setters_replace_values)
{
	int a = 1;
	int b = 2;
	int c = 3;
	Pair *p = pair_new(&a, &b);

	pair_set_first(p, &c);
	ASSERT_EQ_PTR(pair_first(p), &c);
	pair_set_second(p, &a);
	ASSERT_EQ_PTR(pair_second(p), &a);
	pair_delete(p);
}

TEST(pair, swap_exchanges_both_slots)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	Pair *p1 = pair_new(&a, &b);
	Pair *p2 = pair_new(&c, &d);

	pair_swap(p1, p2);
	ASSERT_EQ_PTR(pair_first(p1), &c);
	ASSERT_EQ_PTR(pair_second(p1), &d);
	ASSERT_EQ_PTR(pair_first(p2), &a);
	ASSERT_EQ_PTR(pair_second(p2), &b);
	pair_delete(p1);
	pair_delete(p2);
}

TEST(pair, accessors_on_null_are_safe)
{
	ASSERT_NULL(pair_first(NULL));
	ASSERT_NULL(pair_second(NULL));
	pair_set_first(NULL, NULL);
	pair_set_second(NULL, NULL);
	pair_swap(NULL, NULL);
	pair_delete(NULL);
}
