/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

Pair *pair_new(void *first, void *second)
{
    Pair *pair;

    if (!(pair = malloc(sizeof(Pair))))
        return (NULL);
    pair->first = first;
    pair->second = second;
    return (pair);
}

/* Frees the Pair struct only; first/second ownership stays with the caller. */
void pair_delete(Pair *pair)
{
    free(pair);
}

void *pair_first(Pair *pair)
{
    if (!pair)
        return (NULL);
    return (pair->first);
}

void *pair_second(Pair *pair)
{
    if (!pair)
        return (NULL);
    return (pair->second);
}

void pair_set_first(Pair *pair, void *first)
{
    if (!pair)
        return ;
    pair->first = first;
}

void pair_set_second(Pair *pair, void *second)
{
    if (!pair)
        return ;
    pair->second = second;
}

void pair_swap(Pair *a, Pair *b)
{
    void *tmp_first;
    void *tmp_second;

    if (!a || !b)
        return ;
    tmp_first = a->first;
    tmp_second = a->second;
    a->first = b->first;
    a->second = b->second;
    b->first = tmp_first;
    b->second = tmp_second;
}
