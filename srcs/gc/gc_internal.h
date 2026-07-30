/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_INTERNAL_H
#define GC_INTERNAL_H

#include <libft.h>
#include <stdint.h>
#include <setjmp.h>

#define GC_INITIAL_CAPACITY 64
#define GC_INITIAL_THRESHOLD (1 << 20)
#define GC_MAX_LOAD_NUM 7
#define GC_MAX_LOAD_DEN 10

/* The conservative scan deliberately reads raw stack bytes that may fall
** inside ASan's stack redzones (bytes outside a variable's declared
** extent) - that's the whole point of a conservative scan, so it must
** stay un-instrumented rather than have ASan treat it as an overflow. */
#if defined(__has_attribute)
# if __has_attribute(no_sanitize)
#  define GC_NO_SANITIZE_ADDRESS __attribute__((no_sanitize("address")))
# endif
#endif
#ifndef GC_NO_SANITIZE_ADDRESS
# define GC_NO_SANITIZE_ADDRESS
#endif

typedef enum e_gc_slot
{
    GC_EMPTY = 0,
    GC_USED,
    GC_DEAD
}   t_gc_slot;

typedef struct s_gc_block
{
    void        *ptr;
    size_t      size;
    bool        marked;
    t_gc_slot   slot;
}   t_gc_block;

typedef struct s_gc_root
{
    void                **addr;
    struct s_gc_root    *next;
}   t_gc_root;

typedef struct s_gc_state
{
    t_gc_block  *blocks;
    size_t      capacity;
    size_t      count;
    size_t      tombstones;
    size_t      live_bytes;
    size_t      bytes_since_collect;
    size_t      collect_threshold;
    size_t      collections_run;
    void        *stack_bottom;
    t_gc_root   *roots;
    bool        initialized;
}   t_gc_state;

/* One sorted-by-address snapshot of the live blocks, built once per
** gc_collect() call so containment checks during marking are a binary
** search (O(log n)) instead of a scan of the whole table (O(n)). */
typedef struct s_gc_scan
{
    t_gc_block  **entries;
    size_t      count;
    t_gc_block  **worklist;
    size_t      worklist_len;
    size_t      worklist_cap;
}   t_gc_scan;

extern t_gc_state g_gc;

bool        gc_table_init(void);
bool        gc_table_insert(void *ptr, size_t size);
t_gc_block  *gc_table_find(void *ptr);
void        gc_table_remove(void *ptr);
void        gc_table_destroy(void);

void        gc_roots_clear(void);
void        gc_mark_roots(t_gc_scan *scan);

GC_NO_SANITIZE_ADDRESS
void        gc_mark_range(t_gc_scan *scan, void *lo, void *hi);

#endif
