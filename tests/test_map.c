/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(map, new_null_compare_returns_null)
{
	ASSERT_NULL(map_new(NULL));
}

TEST(map, insert_and_get_int_keys)
{
	int keys[] = {1, 2, 3};
	char *values[] = {"one", "two", "three"};
	Map *m = map_new(compare_pair_int);

	for (int i = 0; i < 3; ++i)
		map_insert(m, &keys[i], values[i]);
	ASSERT_EQ_UINT(map_size(m), 3);
	ASSERT_EQ_STR((char *)map_get(m, &keys[1]), "two");
	map_delete(m, true);
}

TEST(map, get_missing_key_returns_null)
{
	int key = 1;
	int absent = 2;
	Map *m = map_new(compare_pair_int);

	map_insert(m, &key, "value");
	ASSERT_NULL(map_get(m, &absent));
	map_delete(m, true);
}

TEST(map, insert_same_key_updates_value)
{
	int key = 1;
	Map *m = map_new(compare_pair_int);

	map_insert(m, &key, "first");
	map_insert(m, &key, "second");
	ASSERT_EQ_UINT(map_size(m), 1);
	ASSERT_EQ_STR((char *)map_get(m, &key), "second");
	map_delete(m, true);
}

TEST(map, contains_reflects_state)
{
	int key = 1;
	int absent = 2;
	Map *m = map_new(compare_pair_int);

	map_insert(m, &key, "value");
	ASSERT(map_contains(m, &key));
	ASSERT(!map_contains(m, &absent));
	map_delete(m, true);
}

TEST(map, remove_returns_value_and_shrinks)
{
	int key = 1;
	Map *m = map_new(compare_pair_int);

	map_insert(m, &key, "value");
	ASSERT_EQ_STR((char *)map_remove(m, &key), "value");
	ASSERT_EQ_UINT(map_size(m), 0);
	ASSERT(!map_contains(m, &key));
	map_delete(m, true);
}

TEST(map, remove_absent_key_returns_null)
{
	int key = 1;
	int absent = 2;
	Map *m = map_new(compare_pair_int);

	map_insert(m, &key, "value");
	ASSERT_NULL(map_remove(m, &absent));
	map_delete(m, true);
}

TEST(map, is_empty_reflects_state)
{
	int key = 1;
	Map *m = map_new(compare_pair_int);

	ASSERT(map_is_empty(m));
	map_insert(m, &key, "value");
	ASSERT(!map_is_empty(m));
	map_delete(m, true);
}

/* compare_pair_str expects char** (address of key), not a bare char*. */
TEST(map, string_keys_via_compare_pair_str)
{
	const char *keys[] = {"alice", "bob"};
	const char *lookup = "bob";
	int ages[] = {30, 25};
	Map *m = map_new(compare_pair_str);

	map_insert(m, &keys[0], &ages[0]);
	map_insert(m, &keys[1], &ages[1]);
	ASSERT_EQ_INT(*(int *)map_get(m, &lookup), 25);
	map_delete(m, true);
}

TEST(map, delete_null_is_safe)
{
	map_delete(NULL, false);
}
