/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(stack, new_is_empty)
{
	Stack *s = stack_new();

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_UINT(stack_size(s), 0);
	ASSERT(stack_empty(s));
	stack_delete(s);
}

TEST(stack, push_and_top_lifo_order)
{
	int a = 1;
	int b = 2;
	int c = 3;
	Stack *s = stack_new();

	stack_push(s, &a);
	stack_push(s, &b);
	stack_push(s, &c);
	ASSERT_EQ_UINT(stack_size(s), 3);
	ASSERT_EQ_PTR(stack_top(s), &c);
	stack_delete(s);
}

TEST(stack, pop_removes_in_lifo_order)
{
	int a = 1;
	int b = 2;
	int c = 3;
	Stack *s = stack_new();

	stack_push(s, &a);
	stack_push(s, &b);
	stack_push(s, &c);
	stack_pop(s);
	ASSERT_EQ_PTR(stack_top(s), &b);
	stack_pop(s);
	ASSERT_EQ_PTR(stack_top(s), &a);
	ASSERT_EQ_UINT(stack_size(s), 1);
	stack_delete(s);
}

TEST(stack, top_and_pop_on_empty_are_safe)
{
	Stack *s = stack_new();

	ASSERT_NULL(stack_top(s));
	stack_pop(s);
	ASSERT_EQ_UINT(stack_size(s), 0);
	stack_delete(s);
}

TEST(stack, delete_null_is_safe)
{
	stack_delete(NULL);
}

TEST(stack, many_pushes_then_pops_stays_consistent)
{
	int values[50];
	Stack *s = stack_new();

	for (int i = 0; i < 50; ++i)
	{
		values[i] = i;
		stack_push(s, &values[i]);
	}
	for (int i = 49; i >= 0; --i)
	{
		ASSERT_EQ_INT(*(int *)stack_top(s), i);
		stack_pop(s);
	}
	ASSERT(stack_empty(s));
	stack_delete(s);
}
