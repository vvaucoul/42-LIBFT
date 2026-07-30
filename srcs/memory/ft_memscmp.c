/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memscmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:30:40 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_memscmp(const void *ptr, const void *ptr_cmp, size_t len, size_t start)
{
    const unsigned char *tmp_ptr;
    const unsigned char *tmp_cmp;
    size_t i;

    if (start > len)
        return (0);
    tmp_ptr = (const unsigned char *)ptr + start;
    tmp_cmp = (const unsigned char *)ptr_cmp + start;
    len -= start;
    i = 0;
    while (i < len)
    {
        if (tmp_ptr[i] != tmp_cmp[i])
            return ((int)tmp_ptr[i] - (int)tmp_cmp[i]);
        ++i;
    }
    return (0);
}
