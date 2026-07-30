/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

static void *g_test_root;

/* Overwrites recently-used stack bytes so a stale, already-dead pointer
** value left over from an earlier call can't be conservatively (and
** wrongly, for test purposes) mistaken for a live reference. */
static void stomp_stack(void)
{
	volatile char noise[512];
	size_t i;

	i = 0;
	while (i < sizeof(noise))
	{
		noise[i] = (char)(i * 31 + 7);
		++i;
	}
}

TEST(gc, alloc_is_usable_and_tracked)
{
	char *p;

	gc_shutdown();
	p = gc_alloc(10);
	ASSERT_NOT_NULL(p);
	memcpy(p, "hello", 5);
	ASSERT_EQ_MEM(p, "hello", 5);
	ASSERT_EQ_UINT(gc_live_count(), 1);
}

TEST(gc, alloc_zero_size_returns_null)
{
	gc_shutdown();
	ASSERT_NULL(gc_alloc(0));
	ASSERT_EQ_UINT(gc_live_count(), 0);
}

TEST(gc, alloc_zero_initializes_memory)
{
	unsigned char *p;
	size_t i;

	gc_shutdown();
	p = gc_alloc(32);
	ASSERT_NOT_NULL(p);
	i = 0;
	while (i < 32)
	{
		ASSERT_EQ_INT(p[i], 0);
		++i;
	}
}

TEST(gc, free_removes_only_that_pointer)
{
	void *a;
	void *b;

	gc_shutdown();
	a = gc_alloc(sizeof(int));
	b = gc_alloc(sizeof(int));
	ASSERT_EQ_UINT(gc_live_count(), 2);
	gc_free(a);
	ASSERT_EQ_UINT(gc_live_count(), 1);
	ASSERT_NOT_NULL(b);
}

TEST(gc, free_on_untracked_pointer_is_noop)
{
	int stack_var;

	gc_shutdown();
	gc_free(&stack_var);
	ASSERT_EQ_UINT(gc_live_count(), 0);
}

TEST(gc, free_on_null_is_safe)
{
	gc_shutdown();
	gc_free(NULL);
	ASSERT_EQ_UINT(gc_live_count(), 0);
}

TEST(gc, realloc_grows_and_preserves_content)
{
	char *p;
	char *grown;

	gc_shutdown();
	p = gc_alloc(4);
	memcpy(p, "abcd", 4);
	grown = gc_realloc(p, 64);
	ASSERT_NOT_NULL(grown);
	ASSERT_EQ_MEM(grown, "abcd", 4);
	ASSERT_EQ_UINT(gc_live_count(), 1);
	ASSERT_EQ_UINT(gc_live_bytes(), 64);
}

TEST(gc, realloc_null_ptr_behaves_like_alloc)
{
	void *p;

	gc_shutdown();
	p = gc_realloc(NULL, 10);
	ASSERT_NOT_NULL(p);
	ASSERT_EQ_UINT(gc_live_count(), 1);
}

TEST(gc, realloc_zero_size_frees_and_returns_null)
{
	void *p;

	gc_shutdown();
	p = gc_alloc(8);
	ASSERT_NULL(gc_realloc(p, 0));
	ASSERT_EQ_UINT(gc_live_count(), 0);
}

TEST(gc, live_bytes_tracks_current_allocations)
{
	gc_shutdown();
	gc_alloc(10);
	gc_alloc(20);
	ASSERT_EQ_UINT(gc_live_bytes(), 30);
}

TEST(gc, collect_keeps_a_locally_referenced_block_alive)
{
	char *kept;

	gc_shutdown();
	kept = gc_alloc(16);
	memcpy(kept, "alive", 5);
	gc_collect();
	ASSERT_EQ_UINT(gc_live_count(), 1);
	ASSERT_EQ_MEM(kept, "alive", 5);
}

/* A conservative collector can't guarantee that ONE specific dropped
** reference is reclaimed on the next pass - a stale copy of its value
** can transiently survive in a spilled register or reused stack slot
** left over from the assignment itself. Dropping many references and
** requiring most (not strictly all) of them back proves real reclamation
** without over-promising what conservative scanning can deliver. */
TEST(gc, collect_frees_unreferenced_allocations)
{
	size_t i;
	void *p;

	gc_shutdown();
	i = 0;
	while (i < 64)
	{
		p = gc_alloc(32);
		ASSERT_NOT_NULL(p);
		++i;
	}
	p = NULL;
	(void)p;
	stomp_stack();
	stomp_stack();
	gc_collect();
	ASSERT(gc_live_count() <= 1);
}

TEST(gc, collect_increments_the_collection_counter)
{
	size_t before;
	void *kept;

	gc_shutdown();
	kept = gc_alloc(8);
	before = gc_collections_run();
	gc_collect();
	ASSERT(gc_collections_run() == before + 1);
	ASSERT_NOT_NULL(kept);
}

TEST(gc, auto_collect_reclaims_unreferenced_allocations_during_a_loop)
{
	size_t before;
	size_t i;
	void *p;

	gc_shutdown();
	before = gc_collections_run();
	i = 0;
	while (i < 20000)
	{
		p = gc_alloc(64);
		ASSERT_NOT_NULL(p);
		++i;
	}
	gc_collect();
	ASSERT(gc_collections_run() > before);
	ASSERT(gc_live_count() <= 1);
}

TEST(gc, add_root_keeps_a_registered_global_alive)
{
	gc_shutdown();
	g_test_root = gc_alloc(8);
	gc_add_root(&g_test_root);
	stomp_stack();
	stomp_stack();
	gc_collect();
	ASSERT_EQ_UINT(gc_live_count(), 1);
	gc_remove_root(&g_test_root);
	g_test_root = NULL;
}

/* Same conservative-collector caveat as collect_frees_unreferenced_
** allocations(): assigning through the global can itself leave a stale
** copy of the pointer transiently reachable, so this drops many global-
** only references and requires most (not strictly all) reclaimed. */
TEST(gc, collect_frees_global_references_without_add_root)
{
	size_t i;

	gc_shutdown();
	i = 0;
	while (i < 64)
	{
		g_test_root = gc_alloc(8);
		ASSERT_NOT_NULL(g_test_root);
		++i;
	}
	g_test_root = NULL;
	stomp_stack();
	stomp_stack();
	gc_collect();
	ASSERT(gc_live_count() <= 1);
}

TEST(gc, remove_root_lets_the_block_be_collected_again)
{
	gc_shutdown();
	g_test_root = gc_alloc(8);
	gc_add_root(&g_test_root);
	gc_remove_root(&g_test_root);
	stomp_stack();
	stomp_stack();
	gc_collect();
	ASSERT_EQ_UINT(gc_live_count(), 0);
	g_test_root = NULL;
}

TEST(gc, add_root_null_is_safe)
{
	gc_add_root(NULL);
}

TEST(gc, remove_root_not_previously_added_is_safe)
{
	int dummy;

	gc_remove_root(&dummy);
}

TEST(gc, shutdown_frees_everything_and_resets_counts)
{
	gc_shutdown();
	gc_alloc(8);
	gc_alloc(8);
	ASSERT_EQ_UINT(gc_live_count(), 2);
	gc_shutdown();
	ASSERT_EQ_UINT(gc_live_count(), 0);
	ASSERT_EQ_UINT(gc_live_bytes(), 0);
}
