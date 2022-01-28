/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 02:19:31 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 02:22:16 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_memlen(const void *ptr)
{
    unsigned char *tmp = (unsigned char *)ptr;
    size_t i = 0;

    while (tmp)
    {
        ++tmp;
        ++i;
    }
    return (i);
}