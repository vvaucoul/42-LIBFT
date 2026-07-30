/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
#define GC_H

#include <stddef.h>

/*
** Conservative mark-and-sweep garbage collector. gc_alloc() blocks are
** tracked in an internal hash table; gc_collect() finds live ones by
** scanning the C stack and CPU registers for values that look like
** pointers into that table - no manual registration needed for locals,
** that's what "conservative" means here. Call gc_init() once before the
** first gc_alloc()/gc_collect() (call site doesn't matter: the real
** top-of-stack address is read from the OS, not approximated from where
** gc_init() happens to run). Globals/statics live outside the stack and
** need an explicit gc_add_root(). Whatever is still tracked at exit is
** freed unconditionally by an atexit handler registered in gc_init().
*/
void gc_init(void);
void gc_shutdown(void);

void *gc_alloc(size_t size);
void *gc_realloc(void *ptr, size_t size);
void gc_free(void *ptr);

/* Runs a mark-and-sweep pass now (also triggered automatically from
** gc_alloc() once enough bytes have piled up since the last pass). */
void gc_collect(void);

/* Registers/unregisters the address of a global or static `void *`
** variable as an extra scan root, e.g. gc_add_root(&g_head). */
void gc_add_root(void *root_addr);
void gc_remove_root(void *root_addr);

size_t gc_live_count(void);
size_t gc_live_bytes(void);
size_t gc_collections_run(void);

#endif
