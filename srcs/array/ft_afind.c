/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_afind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Linear search over an (array, size, elem_size) buffer; returns a
** pointer to the first element for which compare(elem, target) == 0.
*/
void *ft_afind(void *array, size_t size, size_t elem_size,
    const void *target, CompareFunc compare)
{
    char *ptr;
    size_t i;

    if (!array || !target || !compare)
        return (NULL);
    ptr = (char *)array;
    i = 0;
    while (i < size)
    {
        if (compare(ptr, target) == 0)
            return (ptr);
        ptr += elem_size;
        ++i;
    }
    return (NULL);
}
