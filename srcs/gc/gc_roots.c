/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_roots.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_internal.h"

void gc_add_root(void *root_addr)
{
    t_gc_root *root;

    if (!root_addr)
        return ;
    root = malloc(sizeof(t_gc_root));
    if (!root)
        return ;
    root->addr = (void **)root_addr;
    root->next = g_gc.roots;
    g_gc.roots = root;
}

void gc_remove_root(void *root_addr)
{
    t_gc_root *cur;
    t_gc_root *prev;

    prev = NULL;
    cur = g_gc.roots;
    while (cur)
    {
        if ((void *)cur->addr == root_addr)
        {
            if (prev)
                prev->next = cur->next;
            else
                g_gc.roots = cur->next;
            free(cur);
            return ;
        }
        prev = cur;
        cur = cur->next;
    }
}

void gc_mark_roots(t_gc_scan *scan)
{
    t_gc_root *cur;

    cur = g_gc.roots;
    while (cur)
    {
        gc_mark_range(scan, cur->addr, (char *)cur->addr + sizeof(void *));
        cur = cur->next;
    }
}

void gc_roots_clear(void)
{
    t_gc_root *cur;
    t_gc_root *next;

    cur = g_gc.roots;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    g_gc.roots = NULL;
}
