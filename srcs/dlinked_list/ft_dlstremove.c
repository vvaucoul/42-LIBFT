/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstremove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Unlinks `node` from anywhere in `*lst` (updating `*lst` if it was the
** head) and frees it, in O(1) thanks to the `prev` pointer. */
void ft_dlstremove(t_dlist **lst, t_dlist *node, void (*del)(void *))
{
    if (!lst || !node)
        return ;
    if (node->prev)
        node->prev->next = node->next;
    else
        *lst = node->next;
    if (node->next)
        node->next->prev = node->prev;
    node->next = NULL;
    node->prev = NULL;
    ft_dlstdelone(&node, del);
}
