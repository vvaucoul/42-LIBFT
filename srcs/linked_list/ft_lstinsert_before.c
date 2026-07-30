/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_before.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* `node` must already be part of `*lst`. Walks from the head to find
** its predecessor, since t_list has no `prev` pointer (O(n)). */
void ft_lstinsert_before(t_list **lst, t_list *node, t_list *new)
{
    t_list *cur;

    if (!lst || !node || !new)
        return ;
    if (*lst == node)
    {
        new->next = node;
        *lst = new;
        return ;
    }
    cur = *lst;
    while (cur && cur->next != node)
        cur = cur->next;
    if (!cur)
        return ;
    new->next = node;
    cur->next = new;
}
