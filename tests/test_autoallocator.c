/* ************************************************************************** */
/*   test_autoallocator.c - srcs/auto-allocator/ *.c                          */
/*                                                                            */
/*   _g_auto_allocator is a single process-wide global list: every          */
/*   AA_allocate_ptr()/AA_push_ptr() call appends to the SAME shared list,   */
/*   and AA_get_node_size() reports the cumulative count across every test   */
/*   that has run so far in this process - NOT a per-test count. Each test  */
/*   below calls AA_free() first to reset to a known {NULL, 0} baseline      */
/*   (that is the only reset primitive this module provides) before making  */
/*   any assertions about node counts.                                      */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(autoallocator, allocate_ptr_is_usable_and_tracked)
{
	char *p;

	AA_free();
	p = AA_allocate_ptr(sizeof(char), 10);
	ASSERT_NOT_NULL(p);
	memcpy(p, "hello", 5);
	ASSERT_EQ_MEM(p, "hello", 5);
	ASSERT_EQ_UINT(AA_get_node_size(), 1);
	AA_free();
}

TEST(autoallocator, allocate_ptr_zero_size_or_count_returns_null)
{
	AA_free();
	ASSERT_NULL(AA_allocate_ptr(0, 10));
	ASSERT_NULL(AA_allocate_ptr(sizeof(char), 0));
	ASSERT_EQ_UINT(AA_get_node_size(), 0);
}

TEST(autoallocator, free_ptr_removes_only_that_pointer)
{
	void *a;
	void *b;

	AA_free();
	a = AA_allocate_ptr(sizeof(int), 1);
	b = AA_allocate_ptr(sizeof(int), 1);
	ASSERT_EQ_UINT(AA_get_node_size(), 2);
	AA_free_ptr(a);
	ASSERT_EQ_UINT(AA_get_node_size(), 1);
	(void)b;
	AA_free();
}

TEST(autoallocator, free_ptr_on_untracked_pointer_is_noop)
{
	int stack_var = 1;

	AA_free();
	AA_free_ptr(&stack_var);
	ASSERT_EQ_UINT(AA_get_node_size(), 0);
}

TEST(autoallocator, free_ptr_on_null_is_safe)
{
	AA_free();
	AA_free_ptr(NULL);
	ASSERT_EQ_UINT(AA_get_node_size(), 0);
}

TEST(autoallocator, push_ptr_deduplicates_same_pointer)
{
	/* Must be heap-allocated: AA_free() below will free() it, and a stack
	** address there would abort with "invalid pointer". */
	int *value = malloc(sizeof(int));

	AA_free();
	AA_push_ptr(value);
	AA_push_ptr(value);
	ASSERT_EQ_UINT(AA_get_node_size(), 1);
	AA_free();
}

TEST(autoallocator, free_resets_to_empty)
{
	AA_free();
	AA_allocate_ptr(sizeof(int), 1);
	AA_allocate_ptr(sizeof(int), 1);
	ASSERT_EQ_UINT(AA_get_node_size(), 2);
	AA_free();
	ASSERT_EQ_UINT(AA_get_node_size(), 0);
}

TEST(autoallocator, free_on_already_empty_list_is_safe)
{
	AA_free();
	AA_free();
}
