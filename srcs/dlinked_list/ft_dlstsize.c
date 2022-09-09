/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 00:55:18 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/10 00:55:26 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_dlstsize(t_dlist *lst)
{
    size_t size;

    size = 0;
    while (lst)
    {
        lst = lst->next;
        size++;
    }
    return (size);
}