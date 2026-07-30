/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include "framework/test_framework.h"

static void assert_sorted_ints(int *arr, int n)
{
	int i;

	i = 1;
	while (i < n)
	{
		ASSERT(arr[i - 1] <= arr[i]);
		++i;
	}
}

static void fill_random(int *arr, int n, unsigned int seed)
{
	int i;

	srand(seed);
	i = 0;
	while (i < n)
	{
		arr[i] = rand() % 1000;
		++i;
	}
}

typedef struct s_rec
{
	int key;
	int orig_index;
}	t_rec;

static int compare_rec_key(const void *a, const void *b)
{
	const t_rec *ra = a;
	const t_rec *rb = b;

	return ((ra->key > rb->key) - (ra->key < rb->key));
}

/* ------------------------------------------------------------- ft_qsort */

TEST(sort, qsort_sorts_ascending)
{
	int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6, 0};

	ft_qsort(arr, 10, sizeof(int), compare_int);
	for (int i = 0; i < 10; ++i)
		ASSERT_EQ_INT(arr[i], i);
}

TEST(sort, qsort_empty_and_single_are_safe_noops)
{
	int arr[] = {42};

	ft_qsort(arr, 0, sizeof(int), compare_int);
	ft_qsort(arr, 1, sizeof(int), compare_int);
	ASSERT_EQ_INT(arr[0], 42);
}

TEST(sort, qsort_large_random_array)
{
	int *arr = malloc(5000 * sizeof(int));

	fill_random(arr, 5000, 1);
	ft_qsort(arr, 5000, sizeof(int), compare_int);
	assert_sorted_ints(arr, 5000);
	ASSERT(ft_is_sorted(arr, 5000, sizeof(int), compare_int));
	free(arr);
}

/* Classic quicksort pathological cases that must still complete quickly. */
TEST(sort, qsort_duplicate_heavy_array)
{
	int *arr = malloc(2000 * sizeof(int));

	for (int i = 0; i < 2000; ++i)
		arr[i] = i % 3;
	ft_qsort(arr, 2000, sizeof(int), compare_int);
	assert_sorted_ints(arr, 2000);
	free(arr);
}

TEST(sort, qsort_already_sorted_array)
{
	int *arr = malloc(2000 * sizeof(int));

	for (int i = 0; i < 2000; ++i)
		arr[i] = i;
	ft_qsort(arr, 2000, sizeof(int), compare_int);
	assert_sorted_ints(arr, 2000);
	free(arr);
}

TEST(sort, qsort_reverse_sorted_array)
{
	int *arr = malloc(2000 * sizeof(int));

	for (int i = 0; i < 2000; ++i)
		arr[i] = 2000 - i;
	ft_qsort(arr, 2000, sizeof(int), compare_int);
	assert_sorted_ints(arr, 2000);
	free(arr);
}

TEST(sort, qsort_all_equal_elements)
{
	int arr[100];

	for (int i = 0; i < 100; ++i)
		arr[i] = 7;
	ft_qsort(arr, 100, sizeof(int), compare_int);
	for (int i = 0; i < 100; ++i)
		ASSERT_EQ_INT(arr[i], 7);
}

/* ------------------------------------------------------------- ft_hsort */

TEST(sort, hsort_sorts_ascending)
{
	int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6, 0};

	ft_hsort(arr, 10, sizeof(int), compare_int);
	for (int i = 0; i < 10; ++i)
		ASSERT_EQ_INT(arr[i], i);
}

TEST(sort, hsort_empty_and_single_are_safe_noops)
{
	int arr[] = {42};

	ft_hsort(arr, 0, sizeof(int), compare_int);
	ft_hsort(arr, 1, sizeof(int), compare_int);
	ASSERT_EQ_INT(arr[0], 42);
}

TEST(sort, hsort_large_random_array)
{
	int *arr = malloc(5000 * sizeof(int));

	fill_random(arr, 5000, 2);
	ft_hsort(arr, 5000, sizeof(int), compare_int);
	assert_sorted_ints(arr, 5000);
	free(arr);
}

/* ------------------------------------------------------------- ft_msort */

TEST(sort, msort_sorts_ascending)
{
	int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6, 0};

	ft_msort(arr, 10, sizeof(int), compare_int);
	for (int i = 0; i < 10; ++i)
		ASSERT_EQ_INT(arr[i], i);
}

TEST(sort, msort_empty_and_single_are_safe_noops)
{
	int arr[] = {42};

	ft_msort(arr, 0, sizeof(int), compare_int);
	ft_msort(arr, 1, sizeof(int), compare_int);
	ASSERT_EQ_INT(arr[0], 42);
}

TEST(sort, msort_large_random_array)
{
	int *arr = malloc(5000 * sizeof(int));

	fill_random(arr, 5000, 3);
	ft_msort(arr, 5000, sizeof(int), compare_int);
	assert_sorted_ints(arr, 5000);
	free(arr);
}

/* ft_msort() is the only sort in this module guaranteed to be stable. */
TEST(sort, msort_is_stable)
{
	t_rec recs[12];
	int i;

	i = 0;
	while (i < 12)
	{
		recs[i].key = i % 4;
		recs[i].orig_index = i;
		++i;
	}
	ft_msort(recs, 12, sizeof(t_rec), compare_rec_key);
	i = 1;
	while (i < 12)
	{
		if (recs[i - 1].key == recs[i].key)
			ASSERT(recs[i - 1].orig_index < recs[i].orig_index);
		++i;
	}
}

/* ------------------------------------------------------------- ft_bsort */

TEST(sort, bsort_sorts_ascending)
{
	int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6, 0};

	ft_bsort(arr, 10, sizeof(int), compare_int);
	for (int i = 0; i < 10; ++i)
		ASSERT_EQ_INT(arr[i], i);
}

TEST(sort, bsort_empty_and_single_are_safe_noops)
{
	int arr[] = {42};

	ft_bsort(arr, 0, sizeof(int), compare_int);
	ft_bsort(arr, 1, sizeof(int), compare_int);
	ASSERT_EQ_INT(arr[0], 42);
}

TEST(sort, bsort_already_sorted_is_fast_and_correct)
{
	int arr[500];

	for (int i = 0; i < 500; ++i)
		arr[i] = i;
	ft_bsort(arr, 500, sizeof(int), compare_int);
	assert_sorted_ints(arr, 500);
}

/* ------------------------------------------------------------- ft_isort */

TEST(sort, isort_sorts_ascending)
{
	int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6, 0};

	ft_isort(arr, 10, sizeof(int), compare_int);
	for (int i = 0; i < 10; ++i)
		ASSERT_EQ_INT(arr[i], i);
}

TEST(sort, isort_empty_and_single_are_safe_noops)
{
	int arr[] = {42};

	ft_isort(arr, 0, sizeof(int), compare_int);
	ft_isort(arr, 1, sizeof(int), compare_int);
	ASSERT_EQ_INT(arr[0], 42);
}

/* ----------------------------------------------------------- ft_sswap */

TEST(sort, sswap_exchanges_elements)
{
	int a = 1;
	int b = 2;

	ft_sswap(&a, &b, sizeof(int));
	ASSERT_EQ_INT(a, 2);
	ASSERT_EQ_INT(b, 1);
}

/* ------------------------------------------------------------- ft_is_sorted */

TEST(sort, is_sorted_true_and_false)
{
	int sorted[] = {1, 2, 3, 4, 5};
	int unsorted[] = {1, 3, 2, 4, 5};

	ASSERT(ft_is_sorted(sorted, 5, sizeof(int), compare_int));
	ASSERT(!ft_is_sorted(unsorted, 5, sizeof(int), compare_int));
}

TEST(sort, is_sorted_equal_adjacent_elements_counts_as_sorted)
{
	int arr[] = {1, 2, 2, 3};

	ASSERT(ft_is_sorted(arr, 4, sizeof(int), compare_int));
}

TEST(sort, is_sorted_empty_and_single_are_vacuously_true)
{
	int arr[] = {42};

	ASSERT(ft_is_sorted(arr, 0, sizeof(int), compare_int));
	ASSERT(ft_is_sorted(arr, 1, sizeof(int), compare_int));
}

/* -------------------------------------------------------- compare_* */

TEST(sort, compare_int_basic_ordering)
{
	int a = 1;
	int b = 2;

	ASSERT(compare_int(&a, &b) < 0);
	ASSERT(compare_int(&b, &a) > 0);
	ASSERT_EQ_INT(compare_int(&a, &a), 0);
}

TEST(sort, compare_char_basic_ordering)
{
	char a = 'a';
	char b = 'b';

	ASSERT(compare_char(&a, &b) < 0);
	ASSERT(compare_char(&b, &a) > 0);
}

TEST(sort, compare_str_basic_ordering)
{
	const char *a = "abc";
	const char *b = "abd";

	ASSERT(compare_str(&a, &b) < 0);
}

/* 0.9 and 0.3 differ by less than 1.0, so a subtract-then-truncate comparator would report them equal. */
TEST(sort, compare_double_sub_one_magnitude_diff)
{
	double a = 0.9;
	double b = 0.3;

	ASSERT(compare_double(&a, &b) > 0);
	ASSERT(compare_double(&b, &a) < 0);
}

TEST(sort, compare_float_sub_one_magnitude_diff)
{
	float a = 0.9f;
	float b = 0.3f;

	ASSERT(compare_float(&a, &b) > 0);
}

/* The ~3e9 difference overflows if truncated down to an int return type. */
TEST(sort, compare_long_overflow_flips_sign)
{
	long a = 3000000000L;
	long b = 0L;

	ASSERT(compare_long(&a, &b) > 0);
}

TEST(sort, compare_ulong_never_negative_by_construction)
{
	unsigned long a = 1UL;
	unsigned long b = 5UL;

	/* A naive `a - b` comparator is broken here: unsigned subtraction never goes negative. */
	ASSERT(compare_ulong(&a, &b) < 0);
	ASSERT(compare_ulong(&b, &a) > 0);
}

TEST(sort, compare_llong_and_ullong_basic_ordering)
{
	long long la = -5;
	long long lb = 5;
	unsigned long long ua = 5;
	unsigned long long ub = 4294967296ULL;

	ASSERT(compare_llong(&la, &lb) < 0);
	ASSERT(compare_ullong(&ua, &ub) < 0);
}
