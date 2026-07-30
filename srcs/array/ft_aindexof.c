/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aindexof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

/*
** Like ft_acontains but returns the matching index, or SIZE_MAX if
** str is not found.
*/
size_t ft_aindexof(const char **array, const char *str)
{
    size_t i;

    if (!array || !str)
        return (SIZE_MAX);
    i = 0;
    while (array[i])
    {
        if (!ft_strcmp(array[i], str))
            return (i);
        ++i;
    }
    return (SIZE_MAX);
}
