/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>
#include "framework/test_framework.h"

TEST(alloc, calloc_zero_initializes)
{
	char *p = ft_calloc(sizeof(char), 10);

	ASSERT_NOT_NULL(p);
	for (int i = 0; i < 10; ++i)
		ASSERT_EQ_INT(p[i], 0);
	free(p);
}

TEST(alloc, calloc_usable_for_requested_count)
{
	char *p = ft_calloc(sizeof(char), 5);

	ASSERT_NOT_NULL(p);
	memcpy(p, "Hello", 5);
	ASSERT_EQ_MEM(p, "Hello", 5);
	free(p);
}

TEST(alloc, calloc_works_for_large_elements)
{
	typedef struct { long a; long b; long c; long d; } t_big;
	t_big *arr = ft_calloc(sizeof(t_big), 2);

	ASSERT_NOT_NULL(arr);
	arr[0] = (t_big){1, 2, 3, 4};
	arr[1] = (t_big){5, 6, 7, 8};
	ASSERT_EQ_INT(arr[0].a, 1);
	ASSERT_EQ_INT(arr[1].d, 8);
	free(arr);
}

/* Frees a chunk of the exact same size right before allocating it, so glibc's
** tcache hands back the same (dirtied) memory and a partial zero-fill would show. */
TEST(alloc, calloc_zero_fills_every_element_not_just_a_prefix)
{
	size_t total = sizeof(int) * (10 + 1);
	void *dirty = malloc(total);

	memset(dirty, 0xAA, total);
	free(dirty);

	int *arr = ft_calloc(sizeof(int), 10);
	ASSERT_NOT_NULL(arr);
	for (int i = 0; i < 10; ++i)
		ASSERT_MSG(arr[i] == 0,
			"ft_calloc(sizeof(int), 10)[%d] should be 0, got %d - the "
			"zero-fill must cover size * (count + 1) bytes, not just "
			"count + 1 raw bytes", i, arr[i]);
	free(arr);
}

TEST(alloc, calloc_zero_size_or_count_is_safe)
{
	void *p;

	p = ft_calloc(0, 10);
	free(p);
	p = ft_calloc(sizeof(int), 0);
	ASSERT_NOT_NULL(p);
	free(p);
}

TEST(alloc, calloc_overflow_returns_null)
{
	ASSERT_NULL(ft_calloc((size_t)-1, (size_t)-1));
}

TEST(alloc, free_nulls_the_callers_pointer)
{
	char *p = malloc(4);

	ft_free((void **)&p);
	ASSERT_NULL(p);
}

TEST(alloc, free_null_is_safe)
{
	ft_free(NULL);
}

TEST(alloc, free_pointer_to_null_is_safe)
{
	char *p = NULL;

	ft_free((void **)&p);
	ASSERT_NULL(p);
}

TEST(alloc, free_each_null_array_is_safe)
{
	ft_free_each(NULL);
}

TEST(alloc, free_each_frees_and_nulls_every_entry)
{
	void *ptrs[4];

	ptrs[0] = malloc(4);
	ptrs[1] = malloc(4);
	ptrs[2] = malloc(4);
	ptrs[3] = NULL;
	ft_free_each(ptrs);
	ASSERT_NULL(ptrs[0]);
	ASSERT_NULL(ptrs[1]);
	ASSERT_NULL(ptrs[2]);
}

TEST(alloc, free_array_null_array_is_safe)
{
	ft_free_array(NULL, 3);
}

TEST(alloc, free_array_frees_n_entries_and_array)
{
	void **ptrs = malloc(sizeof(void *) * 3);

	ptrs[0] = malloc(4);
	ptrs[1] = malloc(4);
	ptrs[2] = malloc(4);
	ft_free_array(ptrs, 3);
}

TEST(alloc, alloc_2d_grid_is_writable)
{
	void **grid = ft_alloc_2d(sizeof(char), 4, 3);

	ASSERT_NOT_NULL(grid);
	for (size_t y = 0; y < 3; ++y)
	{
		ASSERT_NOT_NULL(grid[y]);
		((char *)grid[y])[0] = 'x';
	}
	ft_free_array(grid, 3);
}

TEST(alloc, alloc_2d_grid_with_element_size_smaller_than_pointer)
{
	void **grid = ft_alloc_2d(sizeof(char), 8, 16);
	size_t y;

	ASSERT_NOT_NULL(grid);
	y = 0;
	while (y < 16)
	{
		ASSERT_NOT_NULL(grid[y]);
		memset(grid[y], 'A' + (int)y, 8);
		++y;
	}
	ASSERT_NULL(grid[16]);
	y = 0;
	while (y < 16)
	{
		ASSERT_EQ_INT(((char *)grid[y])[0], 'A' + (int)y);
		++y;
	}
	ft_free_array(grid, 16);
}

TEST(alloc, realloc_from_null_behaves_like_malloc)
{
	char *p = ft_realloc(NULL, 8);

	ASSERT_NOT_NULL(p);
	memcpy(p, "abcdefg", 8);
	ASSERT_EQ_MEM(p, "abcdefg", 8);
	free(p);
}

TEST(alloc, realloc_grow_preserves_all_original_bytes)
{
	char *p = ft_realloc(NULL, 12);

	memcpy(p, "abcdefghijkl", 12);
	p = ft_realloc(p, 32);
	ASSERT_NOT_NULL(p);
	ASSERT_EQ_MEM(p, "abcdefghijkl", 12);
	free(p);
}

TEST(alloc, realloc_shrink_preserves_truncated_prefix)
{
	char *p = ft_realloc(NULL, 16);

	memcpy(p, "abcdefghijklmnop", 16);
	p = ft_realloc(p, 4);
	ASSERT_NOT_NULL(p);
	ASSERT_EQ_MEM(p, "abcd", 4);
	free(p);
}
