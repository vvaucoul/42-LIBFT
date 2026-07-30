/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(vector, new_is_empty)
{
	Vector *v = vector_new(sizeof(int), 4);

	ASSERT_NOT_NULL(v);
	ASSERT_EQ_UINT(vector_size(v), 0);
	ASSERT(vector_empty(v));
	vector_delete(v);
}

TEST(vector, new_with_count_reserves_capacity_without_size)
{
	Vector *v = vector_new(sizeof(void *), 10);

	ASSERT_NOT_NULL(v);
	ASSERT_EQ_UINT(vector_size(v), 0);
	ASSERT(vector_capacity(v) >= 10);
	vector_delete(v);
}

TEST(vector, push_back_grows_size_and_stores_value)
{
	int a = 1;
	int b = 2;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	ASSERT_EQ_UINT(vector_size(v), 2);
	ASSERT_EQ_PTR(vector_at(v, 0), &a);
	ASSERT_EQ_PTR(vector_at(v, 1), &b);
	vector_delete(v);
}

TEST(vector, push_back_many_elements_grows_capacity_correctly)
{
	int values[100];
	Vector *v = vector_new(sizeof(void *), 0);

	for (int i = 0; i < 100; ++i)
	{
		values[i] = i;
		vector_push_back(v, &values[i]);
	}
	ASSERT_EQ_UINT(vector_size(v), 100);
	ASSERT(vector_capacity(v) >= 100);
	for (int i = 0; i < 100; ++i)
		ASSERT_EQ_INT(*(int *)vector_at(v, i), i);
	vector_delete(v);
}

TEST(vector, at_out_of_bounds_returns_null)
{
	Vector *v = vector_new(sizeof(void *), 0);

	ASSERT_NULL(vector_at(v, 0));
	ASSERT_NULL(vector_at(v, 99));
	vector_delete(v);
}

TEST(vector, front_and_back_after_pushes)
{
	int a = 1;
	int b = 2;
	int c = 3;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	vector_push_back(v, &c);
	ASSERT_EQ_PTR(vector_front(v), &a);
	ASSERT_EQ_PTR(vector_back(v), &c);
	vector_delete(v);
}

TEST(vector, front_and_back_on_empty_vector_return_null)
{
	Vector *v = vector_new(sizeof(void *), 0);

	ASSERT_NULL(vector_front(v));
	ASSERT_NULL(vector_back(v));
	vector_delete(v);
}

TEST(vector, data_returns_pointer_to_underlying_array)
{
	int a = 1;
	int b = 2;
	Vector *v = vector_new(sizeof(void *), 0);
	void **raw;

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	raw = (void **)vector_data(v);
	ASSERT_EQ_PTR(raw[0], &a);
	ASSERT_EQ_PTR(raw[1], &b);
	vector_delete(v);
}

TEST(vector, erase_shifts_remaining_elements)
{
	int a = 1;
	int b = 2;
	int c = 3;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	vector_push_back(v, &c);
	vector_erase(v, 1);
	ASSERT_EQ_UINT(vector_size(v), 2);
	ASSERT_EQ_PTR(vector_at(v, 0), &a);
	ASSERT_EQ_PTR(vector_at(v, 1), &c);
	vector_delete(v);
}

TEST(vector, clear_empties_vector_but_keeps_capacity)
{
	int a = 1;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	size_t cap_before = vector_capacity(v);
	vector_clear(v);
	ASSERT_EQ_UINT(vector_size(v), 0);
	ASSERT(vector_empty(v));
	ASSERT_EQ_UINT(vector_capacity(v), cap_before);
	vector_delete(v);
}

TEST(vector, swap_exchanges_two_slots)
{
	int a = 1;
	int b = 2;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	vector_swap(v, 0, 1);
	ASSERT_EQ_PTR(vector_at(v, 0), &b);
	ASSERT_EQ_PTR(vector_at(v, 1), &a);
	vector_delete(v);
}

TEST(vector, insert_updates_size_and_shifts_correctly)
{
	int a = 1;
	int b = 2;
	int c = 3;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	vector_insert(v, &c, 1);
	ASSERT_EQ_UINT(vector_size(v), 3);
	ASSERT_EQ_PTR(vector_at(v, 0), &a);
	ASSERT_EQ_PTR(vector_at(v, 1), &c);
	ASSERT_EQ_PTR(vector_at(v, 2), &b);
	vector_delete(v);
}

TEST(vector, insert_at_end_is_equivalent_to_push_back)
{
	int a = 1;
	int b = 2;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_insert(v, &b, 1);
	ASSERT_EQ_UINT(vector_size(v), 2);
	ASSERT_EQ_PTR(vector_at(v, 1), &b);
	vector_delete(v);
}

TEST(vector, pop_back_on_empty_is_a_safe_noop)
{
	Vector *v = vector_new(sizeof(void *), 0);

	vector_pop_back(v);
	ASSERT_EQ_UINT(vector_size(v), 0);
	vector_delete(v);
}

TEST(vector, pop_back_removes_last_element)
{
	int a = 1;
	int b = 2;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	vector_pop_back(v);
	ASSERT_EQ_UINT(vector_size(v), 1);
	ASSERT_EQ_PTR(vector_back(v), &a);
	vector_delete(v);
}

TEST(vector, reserve_grows_capacity_without_changing_size)
{
	int a = 1;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_reserve(v, 50);
	ASSERT_EQ_UINT(vector_size(v), 1);
	ASSERT(vector_capacity(v) >= 50);
	ASSERT_EQ_PTR(vector_at(v, 0), &a);
	vector_delete(v);
}

TEST(vector, assign_replaces_contents)
{
	int a = 1;
	int b = 2;
	int c = 3;
	void *ptrs[] = {&a, &b, &c, NULL};
	Vector *v = vector_new(sizeof(void *), 0);

	vector_assign(v, ptrs);
	ASSERT_EQ_UINT(vector_size(v), 3);
	ASSERT_EQ_PTR(vector_at(v, 0), &a);
	ASSERT_EQ_PTR(vector_at(v, 2), &c);
	vector_delete(v);
}

TEST(vector, assign_grows_and_copies_all_elements)
{
	int values[10];
	void *ptrs[11];
	Vector *v = vector_new(sizeof(void *), 0);
	int a = 1;

	vector_push_back(v, &a);
	for (int i = 0; i < 10; ++i)
	{
		values[i] = i;
		ptrs[i] = &values[i];
	}
	ptrs[10] = NULL;
	vector_assign(v, ptrs);
	ASSERT_EQ_UINT(vector_size(v), 10);
	for (int i = 0; i < 10; ++i)
		ASSERT_EQ_INT(*(int *)vector_at(v, i), i);
	vector_delete(v);
}
