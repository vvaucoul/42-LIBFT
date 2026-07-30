/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_internal.h"

/* Merge sort: the only stable sort in this module (equal elements keep
** their relative order). Uses a half-open [lo, hi) range internally. */
static void merge(char *arr, char *buf, size_t lo, size_t mid, size_t hi,
        size_t elem_size, CompareFunc compare)
{
    size_t  i;
    size_t  j;
    size_t  k;

    i = lo;
    j = mid;
    k = lo;
    while (i < mid && j < hi)
    {
        if (compare(arr + i * elem_size, arr + j * elem_size) <= 0)
        {
            ft_memcpy(buf + k * elem_size, arr + i * elem_size, elem_size);
            ++i;
        }
        else
        {
            ft_memcpy(buf + k * elem_size, arr + j * elem_size, elem_size);
            ++j;
        }
        ++k;
    }
    while (i < mid)
    {
        ft_memcpy(buf + k * elem_size, arr + i * elem_size, elem_size);
        ++i;
        ++k;
    }
    while (j < hi)
    {
        ft_memcpy(buf + k * elem_size, arr + j * elem_size, elem_size);
        ++j;
        ++k;
    }
    ft_memcpy(arr + lo * elem_size, buf + lo * elem_size,
        (hi - lo) * elem_size);
}

static void merge_sort_range(char *arr, char *buf, size_t lo, size_t hi,
        size_t elem_size, CompareFunc compare)
{
    size_t mid;

    if (hi - lo <= 1)
        return ;
    mid = lo + (hi - lo) / 2;
    merge_sort_range(arr, buf, lo, mid, elem_size, compare);
    merge_sort_range(arr, buf, mid, hi, elem_size, compare);
    merge(arr, buf, lo, mid, hi, elem_size, compare);
}

void ft_msort(void *array, size_t size, size_t elem_size, CompareFunc compare)
{
    char *buf;

    if (size < 2 || !array || !compare)
        return ;
    if (!(buf = malloc(size * elem_size)))
        return ;
    merge_sort_range((char *)array, buf, 0, size, elem_size, compare);
    free(buf);
}
