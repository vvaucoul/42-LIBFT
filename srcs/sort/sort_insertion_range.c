/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_insertion_range.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_internal.h"

/* Shift-based insertion sort over the inclusive range [lo, hi]; `key_buf`
** is caller-allocated and reused across every element inserted. */
void sort_insertion_range(char *arr, size_t lo, size_t hi, size_t elem_size,
        CompareFunc compare, char *key_buf)
{
    size_t i;
    size_t j;

    if (hi <= lo)
        return ;
    i = lo + 1;
    while (i <= hi)
    {
        ft_memcpy(key_buf, arr + i * elem_size, elem_size);
        j = i;
        while (j > lo && compare(arr + (j - 1) * elem_size, key_buf) > 0)
        {
            ft_memcpy(arr + j * elem_size, arr + (j - 1) * elem_size,
                elem_size);
            --j;
        }
        ft_memcpy(arr + j * elem_size, key_buf, elem_size);
        ++i;
    }
}
