/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Unlinks and frees `node` wherever it is in `*lst`. Walks from the head
** to find its predecessor, since t_list has no `prev` pointer (O(n)). */
void ft_lstremove(t_list **lst, t_list *node, void (*del)(void *))
{
    t_list *cur;

    if (!lst || !*lst || !node)
        return ;
    if (*lst == node)
    {
        *lst = node->next;
        node->next = NULL;
        ft_lstdelone(node, del);
        return ;
    }
    cur = *lst;
    while (cur->next && cur->next != node)
        cur = cur->next;
    if (!cur->next)
        return ;
    cur->next = node->next;
    node->next = NULL;
    ft_lstdelone(node, del);
}
