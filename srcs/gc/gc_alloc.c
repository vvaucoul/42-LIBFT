/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_internal.h"

void *gc_alloc(size_t size)
{
    void *ptr;

    if (size == 0)
        return (NULL);
    if (!g_gc.initialized)
        gc_init();
    if (g_gc.bytes_since_collect >= g_gc.collect_threshold)
        gc_collect();
    ptr = calloc(1, size);
    if (!ptr)
        return (NULL);
    if (!gc_table_insert(ptr, size))
    {
        free(ptr);
        return (NULL);
    }
    g_gc.bytes_since_collect += size;
    return (ptr);
}

void *gc_realloc(void *ptr, size_t size)
{
    t_gc_block *blk;
    size_t old_size;
    void *new_ptr;

    if (!ptr)
        return (gc_alloc(size));
    if (size == 0)
    {
        gc_free(ptr);
        return (NULL);
    }
    blk = gc_table_find(ptr);
    if (!blk)
        return (NULL);
    old_size = blk->size;
    gc_table_remove(ptr);
    new_ptr = realloc(ptr, size);
    if (!new_ptr)
    {
        gc_table_insert(ptr, old_size);
        return (NULL);
    }
    if (!gc_table_insert(new_ptr, size))
        return (NULL);
    return (new_ptr);
}

void gc_free(void *ptr)
{
    if (!ptr || !gc_table_find(ptr))
        return ;
    gc_table_remove(ptr);
    free(ptr);
}

size_t gc_live_count(void)
{
    return (g_gc.count);
}

size_t gc_live_bytes(void)
{
    return (g_gc.live_bytes);
}

size_t gc_collections_run(void)
{
    return (g_gc.collections_run);
}
