/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcrm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 02:12:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* No length is returned, so trailing slots keep their old value past
** the new logical end instead of being read past the buffer. */
void *ft_memcrm(void *ptr, char c, size_t len)
{
    unsigned char *tmp_ptr;
    size_t max_len;
    size_t i;

    tmp_ptr = ptr;
    max_len = len;
    while (len--)
    {
        if (tmp_ptr[len] == (unsigned char)c)
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
