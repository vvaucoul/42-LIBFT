/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsrm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:17:23 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* No length is returned, so trailing slots keep their old value past
** the new logical end instead of being read past the buffer. */
void *ft_memsrm(void *ptr, char *str, size_t len)
{
    unsigned char *tmp_ptr;
    size_t max_len;
    size_t i;

    tmp_ptr = ptr;
    max_len = len;
    while (len--)
    {
        if (ft_ccof(tmp_ptr[len], str) == true)
        {
            i = len;
            while (i + 1 < max_len)
            {
                tmp_ptr[i] = tmp_ptr[i + 1];
                ++i;
            }
        }
    }
    return (ptr);
}
