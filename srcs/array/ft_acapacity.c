/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acapacity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:53:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns (row_count + 1) * (longest_row + 1): an upper-bound buffer
** size used as a calloc() size hint (see ft_multijoin()).
*/
size_t ft_acapacity(const char **array)
{
    size_t i;
    size_t j;
    size_t max_x;

    i = 0;
    max_x = 0;
    if (!array)
        return (0);
    while (array[i])
    {
        j = 0;
        while (array[i][j])
            ++j;
        if (j > max_x)
            max_x = j;
        ++i;
    }
    return ((i + 1) * (max_x + 1));
}
