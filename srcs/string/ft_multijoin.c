/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multijoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* joins every string in a NULL-terminated array into one allocation */
char *ft_multijoin(const char **array)
{
    char *new_str;
    size_t i;

    if (!array)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), 1)))
        return (NULL);
    i = 0;
    while (array[i])
    {
        if (!(new_str = ft_fstrjoin(new_str, array[i])))
            return (NULL);
        ++i;
    }
    return (new_str);
}
