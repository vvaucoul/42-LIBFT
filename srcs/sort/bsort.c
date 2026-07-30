/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_internal.h"

/* Optimized bubble sort: shrinks the bound to the last swap position
** each pass and exits early once a full pass makes no swaps. */
void ft_bsort(void *array, size_t size, size_t elem_size, CompareFunc compare)
{
    char    *arr;
    char    *swap_buf;
    size_t  bound;
    size_t  last_swap;
    size_t  i;
    bool    any_swap;

    if (size < 2 || !array || !compare)
        return ;
    if (!(swap_buf = malloc(elem_size)))
        return ;
    arr = (char *)array;
    bound = size - 1;
    while (bound > 0)
    {
        any_swap = false;
        last_swap = 0;
        i = 0;
        while (i < bound)
        {
            if (compare(arr + i * elem_size, arr + (i + 1) * elem_size) > 0)
            {
                sort_swap(arr + i * elem_size, arr + (i + 1) * elem_size,
                    elem_size, swap_buf);
                any_swap = true;
                last_swap = i;
            }
            ++i;
        }
        if (!any_swap)
            break ;
        bound = last_swap;
    }
    free(swap_buf);
}
