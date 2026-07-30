/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_amaxlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:38:07 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the length of the longest string in array, plus one.
*/
size_t ft_amaxlen(const char **array)
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
    return (max_x + 1);
}
