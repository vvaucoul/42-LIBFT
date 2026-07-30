/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstfind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the first node whose data compares equal to `data_ref` via
** `compare`, or NULL if none match. */
t_dlist *ft_dlstfind(t_dlist *lst, const void *data_ref, CompareFunc compare)
{
    if (!compare)
        return (NULL);
    while (lst)
    {
        if (compare(lst->data, data_ref) == 0)
            return (lst);
        lst = lst->next;
    }
    return (NULL);
}
