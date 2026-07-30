/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:04:55 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies forward when dest < ptr, backward otherwise, so overlapping
** regions don't overwrite source bytes before they are read. */
void *ft_memmove(void *dest, const void *ptr, size_t len)
{
    unsigned char *tmp_dest;
    const unsigned char *tmp_ptr;
    size_t i;

    if (!dest || !ptr)
        return (NULL);
    tmp_dest = (unsigned char *)dest;
    tmp_ptr = (const unsigned char *)ptr;
    if (tmp_dest < tmp_ptr)
    {
        i = 0;
        while (i < len)
        {
            tmp_dest[i] = tmp_ptr[i];
            ++i;
        }
    }
    else if (tmp_dest > tmp_ptr)
    {
        while (len--)
            tmp_dest[len] = tmp_ptr[len];
    }
    return (dest);
}
