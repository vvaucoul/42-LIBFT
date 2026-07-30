/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:43:35 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>

void ft_sort_array(void *array, size_t size, size_t elem_size,
    CompareFunc compare)
{
    qsort(array, size, elem_size, compare);
}

/*
** Guards size <= 1 to avoid an unsigned underflow in the `end` pointer
** arithmetic below when size == 0.
*/
void ft_reverse_array(void *array, size_t size, size_t elem_size)
{
    char *start;
    char *end;
    char tmp[elem_size];

    if (size <= 1 || elem_size == 0)
        return ;
    start = (char *)array;
    end = (char *)array + (size - 1) * elem_size;
    while (start < end)
    {
        ft_memcpy(tmp, start, elem_size);
        ft_memcpy(start, end, elem_size);
        ft_memcpy(end, tmp, elem_size);
        start += elem_size;
        end -= elem_size;
    }
}

/*
** Returns a pointer to the largest element (compared byte-wise via
** memcmp), or NULL if the array is empty.
*/
void *ft_max_in_array(void *array, size_t size, size_t elem_size)
{
    char *ptr;
    char *max;
    size_t i;

    if (!array || size == 0)
        return (NULL);
    ptr = (char *)array;
    max = ptr;
    i = 1;
    while (i < size)
    {
        ptr += elem_size;
        if (memcmp(ptr, max, elem_size) > 0)
            max = ptr;
        ++i;
    }
    return (max);
}

void *ft_min_in_array(void *array, size_t size, size_t elem_size)
{
    char *ptr;
    char *min;
    size_t i;

    if (!array || size == 0)
        return (NULL);
    ptr = (char *)array;
    min = ptr;
    i = 1;
    while (i < size)
    {
        ptr += elem_size;
        if (memcmp(ptr, min, elem_size) < 0)
            min = ptr;
        ++i;
    }
    return (min);
}
