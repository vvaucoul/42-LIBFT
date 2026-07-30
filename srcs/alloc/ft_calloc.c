/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:51:18 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

/*
** Allocates size * (count + 1) bytes, all zeroed; the "+1" reserves one
** extra slot for a trailing NUL/sentinel, a convention relied on by callers.
*/
void *ft_calloc(size_t size, size_t count)
{
    void *ptr;
    size_t total;

    if (count == SIZE_MAX)
        return (NULL);
    if (size != 0 && (count + 1) > (SIZE_MAX / size))
        return (NULL);
    total = size * (count + 1);
    if (!(ptr = malloc(total)))
        return (NULL);
    ft_bzero(ptr, total);
    return (ptr);
}
