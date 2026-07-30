/* ************************************************************************** */
/*   test_alloc.c - srcs/alloc/ *.c                                           */
/* ************************************************************************** */

#include <libft.h>
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

/* ft_calloc allocates malloc(sizeof(size_t) * (count + 1)) - the `size`
** argument itself is never used to size the allocation, only `count` is.
** For size <= sizeof(size_t) (8 on 64-bit) this just over-allocates
** harmlessly; for an element size > 8 bytes it under-allocates relative to
** what a real calloc(size, count) contract promises. This test documents
** the bug without relying on a crash (heap slack usually hides it in a
** non-sanitized build - run `make asan` to see it as a real heap overflow). */
TEST(alloc, calloc_ignores_size_for_large_elements_known_bug)
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

TEST(alloc, free_null_is_safe)
{
	ft_free(NULL);
}

TEST(alloc, free_valid_pointer)
{
	char *p = malloc(4);

	ft_free(p);
}

TEST(alloc, multifree_null_array_is_safe)
{
	ft_multifree(NULL);
}

TEST(alloc, multifree_frees_each_entry)
{
	void *ptrs[4];

	ptrs[0] = malloc(4);
	ptrs[1] = malloc(4);
	ptrs[2] = malloc(4);
	ptrs[3] = NULL;
	ft_multifree(ptrs);
}

TEST(alloc, afree_frees_n_entries_and_array)
{
	void **ptrs = malloc(sizeof(void *) * 3);

	ptrs[0] = malloc(4);
	ptrs[1] = malloc(4);
	ptrs[2] = malloc(4);
	ft_afree(ptrs, 3);
}

/* ft_acol's inner cursor `j` is never reset between rows (see the matching
** ft_asize note in test_array.c) - only safe/deterministic to assert on
** for rows of non-decreasing length. */
TEST(alloc, acol_longest_string_plus_one)
{
	const char *arr[] = {"a", "abc", "abcd", NULL};

	ASSERT_EQ_UINT(ft_acol(arr), 5);
}

TEST(alloc, acol_null_array)
{
	ASSERT_EQ_UINT(ft_acol(NULL), 0);
}

TEST(alloc, aalloc_grid_is_writable)
{
	void **grid = ft_aalloc(sizeof(char), 4, 3);

	ASSERT_NOT_NULL(grid);
	for (size_t y = 0; y < 3; ++y)
	{
		ASSERT_NOT_NULL(grid[y]);
		((char *)grid[y])[0] = 'x';
	}
	for (size_t y = 0; y < 3; ++y)
		free(grid[y]);
	free(grid);
}

TEST(alloc, realloc_from_null_behaves_like_malloc)
{
	char *p = ft_realloc(NULL, 8);

	ASSERT_NOT_NULL(p);
	memcpy(p, "abcdefg", 8);
	ASSERT_EQ_MEM(p, "abcdefg", 8);
	free(p);
}

/* ft_realloc treats `cursize` as sizeof(ptr) (always 8, the pointer's own
** size), not the real old allocation size, so growing past 8 bytes only
** ever memcpy's the first 8 bytes of the previous content - everything
** after byte 8 is lost/uninitialized in the new block. */
TEST(alloc, realloc_grow_past_8_bytes_loses_data_known_bug)
{
	char *p = ft_realloc(NULL, 12);

	memcpy(p, "abcdefghijkl", 12);
	p = ft_realloc(p, 32);
	ASSERT_NOT_NULL(p);
	ASSERT_MSG(!memcmp(p, "abcdefghijkl", 12),
		"ft_realloc(p, 32) should preserve all 12 original bytes, but "
		"`cursize = sizeof(ptr)` (always 8) only copies the first 8: "
		"got \"%.12s\"", p);
	free(p);
}
