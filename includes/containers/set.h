/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include "libft.h"

/*
** Like C++'s std::set: an ordered container of unique values. A thin,
** purpose-named wrapper around the already-hardened RBTree (which already
** silently rejects duplicate keys on insert - exactly what a set needs).
*/
typedef struct s_set
{
    RBTree  *tree;
}   t_set;

#define Set t_set

Set     *set_new(CompareFunc compare);
void    set_delete(Set *set, bool free_data);
void    set_insert(Set *set, void *data);
bool    set_contains(Set *set, void *data);
void    *set_remove(Set *set, void *data);
size_t  set_size(Set *set);
bool    set_is_empty(Set *set);

#endif
