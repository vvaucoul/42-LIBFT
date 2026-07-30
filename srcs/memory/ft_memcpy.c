/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:41:43 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memcpy(void *dst, const void *restrict src, size_t len)
{
    if (!dst || !src)
        return (NULL);

    unsigned char *tmp_dst = dst;
    const unsigned char *tmp_src = src;

    for (size_t i = 0; i < len; ++i)
        *(tmp_dst++) = *(tmp_src++);
    return (dst);
}
