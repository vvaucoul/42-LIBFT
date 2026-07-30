/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_internal.h"

/* Thin wrapper: the shift-based logic lives in sort_insertion_range()
** so ft_qsort()'s small-subarray cutoff can reuse the same code. */
void ft_isort(void *array, size_t size, size_t elem_size, CompareFunc compare)
{
    char *key_buf;

    if (size < 2 || !array || !compare)
        return ;
    if (!(key_buf = malloc(elem_size)))
        return ;
    sort_insertion_range((char *)array, 0, size - 1, elem_size, compare,
        key_buf);
    free(key_buf);
}
