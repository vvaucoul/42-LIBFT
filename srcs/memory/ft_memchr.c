/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:37:10 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memchr(const void *ptr, int value, size_t len)
{
    const unsigned char *tmp_ptr;
    size_t i;

    tmp_ptr = (const unsigned char *)ptr;
    i = 0;
    while (i < len)
    {
        if (tmp_ptr[i] == (unsigned char)value)
            return ((void *)(tmp_ptr + i));
        ++i;
    }
    return (NULL);
}
