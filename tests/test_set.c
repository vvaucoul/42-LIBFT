/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(set, new_null_compare_returns_null)
{
	ASSERT_NULL(set_new(NULL));
}

TEST(set, insert_and_contains)
{
	int values[] = {5, 3, 8, 1};
	int absent = 99;
	Set *s = set_new(compare_int);

	for (int i = 0; i < 4; ++i)
		set_insert(s, &values[i]);
	ASSERT_EQ_UINT(set_size(s), 4);
	ASSERT(set_contains(s, &values[0]));
	ASSERT(!set_contains(s, &absent));
	set_delete(s, false);
}

TEST(set, duplicate_insert_does_not_grow_size)
{
	int value = 42;
	int same_value = 42;
	Set *s = set_new(compare_int);

	set_insert(s, &value);
	set_insert(s, &same_value);
	ASSERT_EQ_UINT(set_size(s), 1);
	set_delete(s, false);
}

TEST(set, remove_existing_value)
{
	int values[] = {5, 3, 8};
	Set *s = set_new(compare_int);

	for (int i = 0; i < 3; ++i)
		set_insert(s, &values[i]);
	ASSERT_NOT_NULL(set_remove(s, &values[1]));
	ASSERT_EQ_UINT(set_size(s), 2);
	ASSERT(!set_contains(s, &values[1]));
	set_delete(s, false);
}

TEST(set, remove_absent_value_returns_null)
{
	int value = 1;
	int absent = 2;
	Set *s = set_new(compare_int);

	set_insert(s, &value);
	ASSERT_NULL(set_remove(s, &absent));
	ASSERT_EQ_UINT(set_size(s), 1);
	set_delete(s, false);
}

TEST(set, is_empty_reflects_state)
{
	int value = 1;
	Set *s = set_new(compare_int);

	ASSERT(set_is_empty(s));
	set_insert(s, &value);
	ASSERT(!set_is_empty(s));
	set_delete(s, false);
}

TEST(set, delete_null_is_safe)
{
	set_delete(NULL, false);
}
