/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* Guards size <= 1 before any pointer arithmetic: `(size - 1) * elem_size`
** would otherwise underflow `size_t` when size == 0. */
bool ft_is_sorted(void *array, size_t size, size_t elem_size,
        CompareFunc compare)
{
    char    *ptr;
    char    *end;

    if (size <= 1 || !array || !compare)
        return (true);
    ptr = (char *)array;
    end = (char *)array + (size - 1) * elem_size;
    while (ptr < end)
    {
        if (compare(ptr, ptr + elem_size) > 0)
            return (false);
        ptr += elem_size;
    }
    return (true);
}
