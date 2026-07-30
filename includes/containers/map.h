/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include "libft.h"
#include "pair.h"

/*
** Like C++'s std::map: an ordered key/value container, built on the same
** RBTree used by Set, storing a Pair (key, value) at each node. Since a
** plain CompareFunc has no way to carry extra context/state, `pair_compare`
** must compare two Pair* by their ->first (the key) directly - e.g.
** compare_pair_int()/compare_pair_str() below, provided for the common
** cases, or your own for anything else.
*/
typedef struct s_map
{
    RBTree  *tree;
}   t_map;

#define Map t_map

int     compare_pair_int(const void *a, const void *b);
int     compare_pair_str(const void *a, const void *b);

Map     *map_new(CompareFunc pair_compare);
void    map_delete(Map *map, bool free_pairs);
void    map_insert(Map *map, void *key, void *value);
void    *map_get(Map *map, void *key);
bool    map_contains(Map *map, void *key);
void    *map_remove(Map *map, void *key);
size_t  map_size(Map *map);
bool    map_is_empty(Map *map);

#endif
