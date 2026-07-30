/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* Ready-made pair_compare helpers, keyed by ->first. */
int compare_pair_int(const void *a, const void *b)
{
    return (compare_int(((Pair *)a)->first, ((Pair *)b)->first));
}

int compare_pair_str(const void *a, const void *b)
{
    return (compare_str(((Pair *)a)->first, ((Pair *)b)->first));
}

Map *map_new(CompareFunc pair_compare)
{
    Map *map;

    if (!pair_compare || !(map = malloc(sizeof(Map))))
        return (NULL);
    if (!(map->tree = createRBTree(pair_compare)))
    {
        free(map);
        return (NULL);
    }
    return (map);
}

void map_delete(Map *map, bool free_pairs)
{
    if (!map)
        return ;
    freeRBTree(map->tree, free_pairs);
    free(map);
}

void map_insert(Map *map, void *key, void *value)
{
    Pair probe;
    Node *existing;
    Pair *pair;

    if (!map)
        return ;
    probe.first = key;
    probe.second = NULL;
    existing = rbtree_search(map->tree, &probe);
    if (existing)
    {
        ((Pair *)existing->data)->second = value;
        return ;
    }
    if (!(pair = pair_new(key, value)))
        return ;
    insert(map->tree, pair);
}

void *map_get(Map *map, void *key)
{
    Pair probe;
    Node *node;

    if (!map)
        return (NULL);
    probe.first = key;
    probe.second = NULL;
    node = rbtree_search(map->tree, &probe);
    if (!node)
        return (NULL);
    return (((Pair *)node->data)->second);
}

bool map_contains(Map *map, void *key)
{
    Pair probe;

    if (!map)
        return (false);
    probe.first = key;
    probe.second = NULL;
    return (rbtree_contains(map->tree, &probe));
}

void *map_remove(Map *map, void *key)
{
    Pair probe;
    Pair *removed;
    void *value;

    if (!map)
        return (NULL);
    probe.first = key;
    probe.second = NULL;
    if (!(removed = rbtree_delete(map->tree, &probe)))
        return (NULL);
    value = removed->second;
    free(removed);
    return (value);
}

size_t map_size(Map *map)
{
    if (!map)
        return (0);
    return (rbtree_size(map->tree));
}

bool map_is_empty(Map *map)
{
    if (!map)
        return (true);
    return (rbtree_is_empty(map->tree));
}
