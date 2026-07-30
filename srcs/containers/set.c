/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

Set *set_new(CompareFunc compare)
{
    Set *set;

    if (!compare || !(set = malloc(sizeof(Set))))
        return (NULL);
    if (!(set->tree = createRBTree(compare)))
    {
        free(set);
        return (NULL);
    }
    return (set);
}

void set_delete(Set *set, bool free_data)
{
    if (!set)
        return ;
    freeRBTree(set->tree, free_data);
    free(set);
}

/* RBTree allows duplicate keys, so uniqueness is enforced here. */
void set_insert(Set *set, void *data)
{
    if (!set)
        return ;
    if (rbtree_contains(set->tree, data))
        return ;
    insert(set->tree, data);
}

bool set_contains(Set *set, void *data)
{
    if (!set)
        return (false);
    return (rbtree_contains(set->tree, data));
}

void *set_remove(Set *set, void *data)
{
    if (!set)
        return (NULL);
    return (rbtree_delete(set->tree, data));
}

size_t set_size(Set *set)
{
    if (!set)
        return (0);
    return (rbtree_size(set->tree));
}

bool set_is_empty(Set *set)
{
    if (!set)
        return (true);
    return (rbtree_is_empty(set->tree));
}
