/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(queue, new_is_empty)
{
	Queue *q = queue_new();

	ASSERT_NOT_NULL(q);
	ASSERT_EQ_UINT(queue_size(q), 0);
	ASSERT(queue_empty(q));
	queue_delete(q, false);
}

TEST(queue, push_and_pop_fifo_order)
{
	int a = 1;
	int b = 2;
	int c = 3;
	Queue *q = queue_new();

	queue_push(q, &a);
	queue_push(q, &b);
	queue_push(q, &c);
	ASSERT_EQ_UINT(queue_size(q), 3);
	ASSERT_EQ_PTR(queue_front(q), &a);
	ASSERT_EQ_PTR(queue_back(q), &c);

	ASSERT_EQ_PTR(queue_pop(q), &a);
	ASSERT_EQ_PTR(queue_pop(q), &b);
	ASSERT_EQ_UINT(queue_size(q), 1);
	ASSERT_EQ_PTR(queue_pop(q), &c);
	ASSERT(queue_empty(q));
	queue_delete(q, false);
}

TEST(queue, pop_on_empty_returns_null)
{
	Queue *q = queue_new();

	ASSERT_NULL(queue_pop(q));
	ASSERT_NULL(queue_front(q));
	ASSERT_NULL(queue_back(q));
	queue_delete(q, false);
}

TEST(queue, push_after_draining_still_works)
{
	int a = 1;
	int b = 2;
	Queue *q = queue_new();

	queue_push(q, &a);
	queue_pop(q);
	ASSERT(queue_empty(q));
	queue_push(q, &b);
	ASSERT_EQ_PTR(queue_front(q), &b);
	ASSERT_EQ_PTR(queue_back(q), &b);
	queue_delete(q, false);
}

TEST(queue, delete_null_is_safe)
{
	queue_delete(NULL, false);
}

TEST(queue, delete_with_free_data_frees_payloads)
{
	Queue *q = queue_new();

	queue_push(q, malloc(sizeof(int)));
	queue_push(q, malloc(sizeof(int)));
	queue_delete(q, true);
}

TEST(queue, many_pushes_and_pops_stay_in_order)
{
	int values[50];
	Queue *q = queue_new();

	for (int i = 0; i < 50; ++i)
	{
		values[i] = i;
		queue_push(q, &values[i]);
	}
	for (int i = 0; i < 50; ++i)
		ASSERT_EQ_INT(*(int *)queue_pop(q), i);
	ASSERT(queue_empty(q));
	queue_delete(q, false);
}
