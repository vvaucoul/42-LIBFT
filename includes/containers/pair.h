/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_H
#define PAIR_H

#include <stdlib.h>

/*
** Like C++'s std::pair<T1, T2>: a simple two-value tuple. Both slots are
** void*, so a Pair can hold anything - it's what Map (containers/map.h) uses
** internally to store key/value entries.
*/
typedef struct s_pair
{
    void    *first;
    void    *second;
}   t_pair;

#define Pair t_pair

Pair    *pair_new(void *first, void *second);
void    pair_delete(Pair *pair);
void    *pair_first(Pair *pair);
void    *pair_second(Pair *pair);
void    pair_set_first(Pair *pair, void *first);
void    pair_set_second(Pair *pair, void *second);
void    pair_swap(Pair *a, Pair *b);

#endif
