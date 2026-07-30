/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:24:31 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_memcmp(const void *ptr, const void *ptr_cmp, size_t len)
{
    const unsigned char *tmp_ptr;
    const unsigned char *tmp_cmp;
    size_t i;

    tmp_ptr = (const unsigned char *)ptr;
    tmp_cmp = (const unsigned char *)ptr_cmp;
    i = 0;
    while (i < len)
    {
        if (tmp_ptr[i] != tmp_cmp[i])
            return ((int)tmp_ptr[i] - (int)tmp_cmp[i]);
        ++i;
    }
    return (0);
}
