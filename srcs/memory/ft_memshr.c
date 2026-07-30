/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memshr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:40:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memshr(const void *ptr, const void *cmp, size_t len, size_t nb)
{
    const unsigned char *tmp_ptr;
    size_t i;

    if (nb == 0 || nb > len)
        return (NULL);
    tmp_ptr = (const unsigned char *)ptr;
    i = 0;
    while (i + nb <= len)
    {
        if (!ft_memcmp(tmp_ptr + i, cmp, nb))
            return ((void *)(tmp_ptr + i));
        ++i;
    }
    return (NULL);
}
