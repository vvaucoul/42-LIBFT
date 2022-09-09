/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 00:52:28 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/10 00:52:34 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
    t_dlist *tmp;

    while (*lst)
    {
        tmp = (*lst)->next;
        ft_dlstdelone(lst, del);
        *lst = tmp;
    }
}