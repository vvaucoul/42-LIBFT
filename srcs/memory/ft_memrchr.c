/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Like ft_memchr() but scans backward from the end. */
void *ft_memrchr(const void *ptr, int value, size_t len)
{
    const unsigned char *tmp_ptr;

    tmp_ptr = (const unsigned char *)ptr;
    while (len > 0)
    {
        --len;
        if (tmp_ptr[len] == (unsigned char)value)
            return ((void *)(tmp_ptr + len));
    }
    return (NULL);
}
