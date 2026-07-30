/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_internal.h"

static int compare_block_ptr(const void *a, const void *b)
{
    const t_gc_block *ba;
    const t_gc_block *bb;

    ba = *(const t_gc_block *const *)a;
    bb = *(const t_gc_block *const *)b;
    return ((ba->ptr > bb->ptr) - (ba->ptr < bb->ptr));
}

/* Largest block start <= addr, then checked for containment - turns an
** interior (mid-allocation) pointer value into its owning block. */
static t_gc_block *scan_find_containing(t_gc_scan *scan, uintptr_t addr)
{
    size_t lo;
    size_t hi;
    size_t mid;
    t_gc_block *blk;

    lo = 0;
    hi = scan->count;
    while (lo < hi)
    {
        mid = lo + (hi - lo) / 2;
        if (addr < (uintptr_t)scan->entries[mid]->ptr)
            hi = mid;
        else
            lo = mid + 1;
    }
    if (lo == 0)
        return (NULL);
    blk = scan->entries[lo - 1];
    if (addr >= (uintptr_t)blk->ptr && addr < (uintptr_t)blk->ptr + blk->size)
        return (blk);
    return (NULL);
}

static void scan_push_work(t_gc_scan *scan, t_gc_block *blk)
{
    t_gc_block **grown;
    size_t new_cap;

    if (scan->worklist_len == scan->worklist_cap)
    {
        new_cap = scan->worklist_cap ? scan->worklist_cap * 2 : 16;
        grown = realloc(scan->worklist, new_cap * sizeof(*grown));
        if (!grown)
            return ;
        scan->worklist = grown;
        scan->worklist_cap = new_cap;
    }
    scan->worklist[scan->worklist_len++] = blk;
}

GC_NO_SANITIZE_ADDRESS
void gc_mark_range(t_gc_scan *scan, void *lo, void *hi)
{
    uintptr_t *p;
    uintptr_t *end;
    t_gc_block *blk;

    if (lo >= hi || scan->count == 0)
        return ;
    p = (uintptr_t *)(((uintptr_t)lo + sizeof(uintptr_t) - 1)
            & ~(sizeof(uintptr_t) - 1));
    end = (uintptr_t *)hi;
    while (p + 1 <= end)
    {
        blk = scan_find_containing(scan, *p);
        if (blk && !blk->marked)
        {
            blk->marked = true;
            scan_push_work(scan, blk);
        }
        ++p;
    }
}

static bool gc_build_scan(t_gc_scan *scan)
{
    size_t i;
    size_t idx;

    scan->entries = NULL;
    scan->count = 0;
    scan->worklist = NULL;
    scan->worklist_len = 0;
    scan->worklist_cap = 0;
    if (g_gc.count == 0)
        return (true);
    scan->entries = malloc(g_gc.count * sizeof(t_gc_block *));
    if (!scan->entries)
        return (false);
    idx = 0;
    i = 0;
    while (i < g_gc.capacity)
    {
        if (g_gc.blocks[i].slot == GC_USED)
        {
            g_gc.blocks[i].marked = false;
            scan->entries[idx++] = &g_gc.blocks[i];
        }
        ++i;
    }
    scan->count = idx;
    ft_qsort(scan->entries, scan->count, sizeof(t_gc_block *),
        compare_block_ptr);
    return (true);
}

static void gc_drain_worklist(t_gc_scan *scan)
{
    t_gc_block *blk;

    while (scan->worklist_len > 0)
    {
        blk = scan->worklist[--scan->worklist_len];
        gc_mark_range(scan, blk->ptr, (char *)blk->ptr + blk->size);
    }
}

static void gc_sweep(void)
{
    size_t i;

    i = 0;
    while (i < g_gc.capacity)
    {
        if (g_gc.blocks[i].slot == GC_USED && !g_gc.blocks[i].marked)
        {
            free(g_gc.blocks[i].ptr);
            g_gc.live_bytes -= g_gc.blocks[i].size;
            g_gc.blocks[i].slot = GC_DEAD;
            g_gc.blocks[i].ptr = NULL;
            --g_gc.count;
            ++g_gc.tombstones;
        }
        ++i;
    }
}

void gc_collect(void)
{
    t_gc_scan scan;
    jmp_buf regs;
    void *approx_sp;

    if (!g_gc.initialized || g_gc.count == 0)
        return ;
    if (!gc_build_scan(&scan))
        return ;
    setjmp(regs);
    approx_sp = (void *)&regs;
    gc_mark_range(&scan, approx_sp, g_gc.stack_bottom);
    gc_mark_roots(&scan);
    gc_drain_worklist(&scan);
    gc_sweep();
    free(scan.entries);
    free(scan.worklist);
    g_gc.bytes_since_collect = 0;
    if (g_gc.live_bytes > g_gc.collect_threshold)
        g_gc.collect_threshold = g_gc.live_bytes * 2;
    ++g_gc.collections_run;
}
