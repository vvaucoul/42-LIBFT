/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_internal.h"

/* glibc exports the real top of the initial thread's stack under this
** name (set by the kernel/ld.so before main() runs) - reading it means
** the conservative stack scan always covers the whole stack, regardless
** of where gc_init() itself happens to be called from. */
extern void *__libc_stack_end;

void gc_init(void)
{
    int marker;

    if (g_gc.initialized)
        return ;
    if (!gc_table_init())
        return ;
    g_gc.live_bytes = 0;
    g_gc.bytes_since_collect = 0;
    g_gc.collect_threshold = GC_INITIAL_THRESHOLD;
    g_gc.collections_run = 0;
    g_gc.roots = NULL;
    g_gc.stack_bottom = __libc_stack_end ? __libc_stack_end : (void *)&marker;
    g_gc.initialized = true;
    atexit(gc_shutdown);
}

void gc_shutdown(void)
{
    size_t i;

    if (!g_gc.initialized)
        return ;
    i = 0;
    while (i < g_gc.capacity)
    {
        if (g_gc.blocks[i].slot == GC_USED)
            free(g_gc.blocks[i].ptr);
        ++i;
    }
    gc_table_destroy();
    gc_roots_clear();
    g_gc.collections_run = 0;
    g_gc.initialized = false;
}
