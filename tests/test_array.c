/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(array, acontains_found_and_missing)
{
	const char *arr[] = {"foo", "bar", "baz", NULL};

	ASSERT(ft_acontains(arr, "bar") == true);
	ASSERT(ft_acontains(arr, "qux") == false);
	ASSERT(ft_acontains(NULL, "bar") == false);
	ASSERT(ft_acontains(arr, NULL) == false);
}

TEST(array, aindexof_found_and_missing)
{
	const char *arr[] = {"foo", "bar", "baz", NULL};

	ASSERT_EQ_UINT(ft_aindexof(arr, "bar"), 1);
	ASSERT_EQ_UINT(ft_aindexof(arr, "foo"), 0);
	ASSERT_EQ_UINT(ft_aindexof(arr, "qux"), (size_t)-1);
	ASSERT_EQ_UINT(ft_aindexof(NULL, "bar"), (size_t)-1);
}

TEST(array, alen_counts_entries)
{
	const char *arr[] = {"a", "b", "c", NULL};
	const char *empty[] = {NULL};

	ASSERT_EQ_UINT(ft_alen(arr), 3);
	ASSERT_EQ_UINT(ft_alen(empty), 0);
	ASSERT_EQ_UINT(ft_alen(NULL), 0);
}

/* Rows are in decreasing length order, so a cursor not reset between rows would read out of bounds. */
TEST(array, acapacity_resets_cursor_between_shorter_rows)
{
	const char *arr[] = {"abc", "a", NULL};

	ASSERT_EQ_UINT(ft_acapacity(arr), (2 + 1) * (3 + 1));
}

TEST(array, acapacity_uses_longest_row_and_count)
{
	const char *arr[] = {"a", "bb", "ccc", NULL};

	ASSERT_EQ_UINT(ft_acapacity(arr), (3 + 1) * (3 + 1));
	ASSERT_EQ_UINT(ft_acapacity(NULL), 0);
}

TEST(array, amaxlen_resets_cursor_between_shorter_rows)
{
	const char *arr[] = {"abc", "a", NULL};

	ASSERT_EQ_UINT(ft_amaxlen(arr), 3 + 1);
}

TEST(array, amaxlen_returns_longest_row_len_plus_one)
{
	const char *arr[] = {"a", "bb", "ccc", NULL};

	ASSERT_EQ_UINT(ft_amaxlen(arr), 3 + 1);
	ASSERT_EQ_UINT(ft_amaxlen(NULL), 0);
}

TEST(array, split_basic)
{
	char **words = ft_split("a,bb,ccc", ',');

	ASSERT_NOT_NULL(words);
	ASSERT_EQ_STR(words[0], "a");
	ASSERT_EQ_STR(words[1], "bb");
	ASSERT_EQ_STR(words[2], "ccc");
	ASSERT_NULL(words[3]);
}

TEST(array, split_consecutive_and_edge_delimiters)
{
	char **words = ft_split(",a,,b,", ',');

	ASSERT_NOT_NULL(words);
	ASSERT_EQ_STR(words[0], "");
	ASSERT_EQ_STR(words[1], "a");
	ASSERT_EQ_STR(words[2], "");
	ASSERT_EQ_STR(words[3], "b");
	ASSERT_EQ_STR(words[4], "");
	ASSERT_NULL(words[5]);
}

TEST(array, split_no_delimiter_present)
{
	char **words = ft_split("hello", ',');

	ASSERT_NOT_NULL(words);
	ASSERT_EQ_STR(words[0], "hello");
	ASSERT_NULL(words[1]);
}

TEST(array, split_null_returns_null)
{
	ASSERT_NULL(ft_split(NULL, ','));
}

TEST(array, acpy_copies_every_string)
{
	const char *arr[] = {"foo", "bar", "baz", NULL};
	char **copy = ft_acpy(arr);

	ASSERT_NOT_NULL(copy);
	ASSERT_EQ_STR(copy[0], "foo");
	ASSERT_EQ_STR(copy[1], "bar");
	ASSERT_EQ_STR(copy[2], "baz");
	ASSERT_NULL(copy[3]);
	/* independent copies, not aliases of the originals */
	ASSERT(copy[0] != arr[0]);
	ft_free_array((void **)copy, 3);
}

TEST(array, acpy_empty_array)
{
	const char *arr[] = {NULL};
	char **copy = ft_acpy(arr);

	ASSERT_NOT_NULL(copy);
	ASSERT_NULL(copy[0]);
	ft_free_array((void **)copy, 0);
}

TEST(array, acpy_null_returns_null)
{
	ASSERT_NULL(ft_acpy(NULL));
}

TEST(array, sort_array_ints)
{
	int arr[] = {5, 3, 4, 1, 2};

	ft_sort_array(arr, 5, sizeof(int), compare_int);
	for (int i = 0; i < 5; ++i)
		ASSERT_EQ_INT(arr[i], i + 1);
}

TEST(array, reverse_array_ints)
{
	int arr[] = {1, 2, 3, 4, 5};

	ft_reverse_array(arr, 5, sizeof(int));
	ASSERT_EQ_INT(arr[0], 5);
	ASSERT_EQ_INT(arr[1], 4);
	ASSERT_EQ_INT(arr[2], 3);
	ASSERT_EQ_INT(arr[3], 2);
	ASSERT_EQ_INT(arr[4], 1);
}

TEST(array, reverse_array_empty_and_single_are_safe_noops)
{
	int arr[] = {42};

	ft_reverse_array(arr, 0, sizeof(int));
	ft_reverse_array(arr, 1, sizeof(int));
	ASSERT_EQ_INT(arr[0], 42);
}

TEST(array, min_in_array_small_values)
{
	int arr[] = {5, 3, 9, 1, 7};
	void *min = ft_min_in_array(arr, 5, sizeof(int));

	ASSERT_NOT_NULL(min);
	ASSERT_EQ_INT(*(int *)min, 1);
}

TEST(array, max_in_array_values_larger_than_one_byte)
{
	int arr[] = {300, 5, 1};
	void *max = ft_max_in_array(arr, 3, sizeof(int));

	ASSERT_NOT_NULL(max);
	ASSERT_EQ_INT(*(int *)max, 300);
}

TEST(array, max_and_min_in_array_return_pointer_into_original_array)
{
	int arr[] = {5, 3, 9, 1, 7};
	void *max = ft_max_in_array(arr, 5, sizeof(int));
	void *min = ft_min_in_array(arr, 5, sizeof(int));

	ASSERT_EQ_PTR(max, &arr[2]);
	ASSERT_EQ_PTR(min, &arr[3]);
}

TEST(array, max_and_min_in_array_empty_returns_null)
{
	int arr[] = {1};

	ASSERT_NULL(ft_max_in_array(arr, 0, sizeof(int)));
	ASSERT_NULL(ft_min_in_array(arr, 0, sizeof(int)));
}

TEST(array, afind_locates_matching_element)
{
	int arr[] = {5, 3, 9, 1, 7};
	int target = 9;
	void *found = ft_afind(arr, 5, sizeof(int), &target, compare_int);

	ASSERT_EQ_PTR(found, &arr[2]);
}

TEST(array, afind_no_match_returns_null)
{
	int arr[] = {5, 3, 9, 1, 7};
	int target = 42;

	ASSERT_NULL(ft_afind(arr, 5, sizeof(int), &target, compare_int));
}

TEST(array, afind_null_args_are_safe)
{
	int arr[] = {1, 2, 3};
	int target = 1;

	ASSERT_NULL(ft_afind(NULL, 3, sizeof(int), &target, compare_int));
	ASSERT_NULL(ft_afind(arr, 3, sizeof(int), NULL, compare_int));
}
