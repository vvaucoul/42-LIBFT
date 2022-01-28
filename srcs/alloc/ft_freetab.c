/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:22:00 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 17:23:09 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_freetab(void **ptr)
{
    if (!ptr)
        return;
    for (size_t i = 0; ptr[i]; ++i)
        ft_free(ptr[i]);
    ft_free(ptr);
}