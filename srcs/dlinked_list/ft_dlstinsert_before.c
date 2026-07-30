/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstinsert_before.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* `node` must already be part of `*lst`. Inserting before an arbitrary
** node in O(1) needs the `prev` pointer a singly linked list doesn't have. */
void ft_dlstinsert_before(t_dlist **lst, t_dlist *node, t_dlist *new)
{
    if (!lst || !node || !new)
        return ;
    new->next = node;
    new->prev = node->prev;
    if (node->prev)
        node->prev->next = new;
    else
        *lst = new;
    node->prev = new;
}
