/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:50:42 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memlower(void *ptr, size_t len)
{
    unsigned char *tmp_ptr;
    size_t i;

    tmp_ptr = ptr;
    i = 0;
    while (i < len)
    {
        if (ft_isupper(tmp_ptr[i]))
            tmp_ptr[i] = ft_tolower(tmp_ptr[i]);
        ++i;
    }
    return (ptr);
}
