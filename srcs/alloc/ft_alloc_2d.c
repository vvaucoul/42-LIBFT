/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:20:59 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Builds size_y rows of size_x + 1 elements each; frees everything
** allocated so far if a later row's allocation fails.
*/
void **ft_alloc_2d(size_t size, size_t size_x, size_t size_y)
{
    void **tab;
    size_t i;

    if (!(tab = ft_calloc(sizeof(void *), size_y + 1)))
        return (NULL);
    i = 0;
    while (i < size_y)
    {
        if (!(tab[i] = ft_calloc(size, size_x + 1)))
        {
            ft_free_array(tab, i);
            return (NULL);
        }
        ++i;
    }
    tab[size_y] = NULL;
    return (tab);
}
