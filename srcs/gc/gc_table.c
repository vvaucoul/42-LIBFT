/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_internal.h"

t_gc_state g_gc;

/* Fibonacci (multiplicative) hashing: alignment bits are dropped first
** since every malloc'd pointer is at least 16-byte aligned, then the
** high bits of the product (the well-mixed ones) pick the bucket. */
static size_t gc_hash(void *ptr, size_t capacity)
{
    uintptr_t x;

    x = ((uintptr_t)ptr) >> 4;
    x *= 0x9E3779B97F4A7C15ULL;
    return ((size_t)(x >> 32) & (capacity - 1));
}

bool gc_table_init(void)
{
    g_gc.blocks = calloc(GC_INITIAL_CAPACITY, sizeof(t_gc_block));
    if (!g_gc.blocks)
        return (false);
    g_gc.capacity = GC_INITIAL_CAPACITY;
    g_gc.count = 0;
    g_gc.tombstones = 0;
    return (true);
}

static bool gc_table_grow(void)
{
    t_gc_block *old_blocks;
    size_t old_capacity;
    size_t new_capacity;
    size_t i;
    size_t idx;

    old_blocks = g_gc.blocks;
    old_capacity = g_gc.capacity;
    new_capacity = old_capacity * 2;
    g_gc.blocks = calloc(new_capacity, sizeof(t_gc_block));
    if (!g_gc.blocks)
    {
        g_gc.blocks = old_blocks;
        return (false);
    }
    g_gc.capacity = new_capacity;
    g_gc.tombstones = 0;
    i = 0;
    while (i < old_capacity)
    {
        if (old_blocks[i].slot == GC_USED)
        {
            idx = gc_hash(old_blocks[i].ptr, new_capacity);
            while (g_gc.blocks[idx].slot == GC_USED)
                idx = (idx + 1) & (new_capacity - 1);
            g_gc.blocks[idx] = old_blocks[i];
        }
        ++i;
    }
    free(old_blocks);
    return (true);
}

static bool gc_table_needs_growth(void)
{
    return ((g_gc.count + g_gc.tombstones + 1) * GC_MAX_LOAD_DEN
        > g_gc.capacity * GC_MAX_LOAD_NUM);
}

bool gc_table_insert(void *ptr, size_t size)
{
    size_t idx;

    if (gc_table_needs_growth() && !gc_table_grow())
        return (false);
    idx = gc_hash(ptr, g_gc.capacity);
    while (g_gc.blocks[idx].slot == GC_USED)
        idx = (idx + 1) & (g_gc.capacity - 1);
    g_gc.blocks[idx].ptr = ptr;
    g_gc.blocks[idx].size = size;
    g_gc.blocks[idx].marked = false;
    g_gc.blocks[idx].slot = GC_USED;
    ++g_gc.count;
    g_gc.live_bytes += size;
    return (true);
}

t_gc_block *gc_table_find(void *ptr)
{
    size_t idx;
    size_t probed;

    if (g_gc.capacity == 0)
        return (NULL);
    idx = gc_hash(ptr, g_gc.capacity);
    probed = 0;
    while (g_gc.blocks[idx].slot != GC_EMPTY && probed < g_gc.capacity)
    {
        if (g_gc.blocks[idx].slot == GC_USED && g_gc.blocks[idx].ptr == ptr)
            return (&g_gc.blocks[idx]);
        idx = (idx + 1) & (g_gc.capacity - 1);
        ++probed;
    }
    return (NULL);
}

void gc_table_remove(void *ptr)
{
    t_gc_block *blk;

    blk = gc_table_find(ptr);
    if (!blk)
        return ;
    g_gc.live_bytes -= blk->size;
    blk->slot = GC_DEAD;
    blk->ptr = NULL;
    --g_gc.count;
    ++g_gc.tombstones;
}

void gc_table_destroy(void)
{
    free(g_gc.blocks);
    g_gc.blocks = NULL;
    g_gc.capacity = 0;
    g_gc.count = 0;
    g_gc.tombstones = 0;
    g_gc.live_bytes = 0;
}
