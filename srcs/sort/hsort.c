/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_internal.h"

/* Indices are relative to `lo`, only converted to absolute offsets when
** touching `arr` - lets the same code sort a sub-range or the whole array. */
static void sift_down(char *arr, size_t lo, size_t n, size_t root,
        size_t elem_size, CompareFunc compare, char *swap_buf)
{
    size_t largest;
    size_t left;
    size_t right;

    while (1)
    {
        largest = root;
        left = 2 * root + 1;
        right = 2 * root + 2;
        if (left < n && compare(arr + (lo + left) * elem_size,
                arr + (lo + largest) * elem_size) > 0)
            largest = left;
        if (right < n && compare(arr + (lo + right) * elem_size,
                arr + (lo + largest) * elem_size) > 0)
            largest = right;
        if (largest == root)
            return ;
        sort_swap(arr + (lo + root) * elem_size,
            arr + (lo + largest) * elem_size, elem_size, swap_buf);
        root = largest;
    }
}

void sort_heapsort_range(char *arr, size_t lo, size_t hi, size_t elem_size,
        CompareFunc compare, char *swap_buf)
{
    size_t  n;
    size_t  i;
    size_t  end;

    if (hi <= lo)
        return ;
    n = hi - lo + 1;
    i = n / 2;
    while (i > 0)
    {
        --i;
        sift_down(arr, lo, n, i, elem_size, compare, swap_buf);
    }
    end = n - 1;
    while (end > 0)
    {
        sort_swap(arr + lo * elem_size, arr + (lo + end) * elem_size,
            elem_size, swap_buf);
        sift_down(arr, lo, end, 0, elem_size, compare, swap_buf);
        --end;
    }
}

void ft_hsort(void *array, size_t size, size_t elem_size, CompareFunc compare)
{
    char *swap_buf;

    if (size < 2 || !array || !compare)
        return ;
    if (!(swap_buf = malloc(elem_size)))
        return ;
    sort_heapsort_range((char *)array, 0, size - 1, elem_size, compare,
        swap_buf);
    free(swap_buf);
}
