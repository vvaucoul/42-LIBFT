/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstreverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Reverses the list in place by swapping `next`/`prev` on every node - a
** singly linked list would need to rebuild the chain node by node instead. */
void ft_dlstreverse(t_dlist **lst)
{
    t_dlist *cur;
    t_dlist *next;
    t_dlist *last;

    if (!lst || !*lst)
        return ;
    cur = *lst;
    last = cur;
    while (cur)
    {
        next = cur->next;
        cur->next = cur->prev;
        cur->prev = next;
        last = cur;
        cur = next;
    }
    *lst = last;
}
