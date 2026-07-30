/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstinsert_after.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* `node` must already be part of the list; inserting after it never
** changes the head, so no `t_dlist **` is needed. */
void ft_dlstinsert_after(t_dlist *node, t_dlist *new)
{
    if (!node || !new)
        return ;
    new->prev = node;
    new->next = node->next;
    if (node->next)
        node->next->prev = new;
    node->next = new;
}
