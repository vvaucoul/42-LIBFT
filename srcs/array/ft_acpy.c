/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:25:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Duplicates every string in arr into a freshly allocated array; frees
** everything copied so far if a later ft_strdup fails.
*/
char **ft_acpy(const char **arr)
{
    char **new_array;
    size_t i;

    if (!arr)
        return (NULL);
    if (!(new_array = ft_calloc(sizeof(char *), ft_alen(arr) + 1)))
        return (NULL);
    i = 0;
    while (arr[i])
    {
        if (!(new_array[i] = ft_strdup(arr[i])))
        {
            ft_free_array((void **)new_array, i);
            return (NULL);
        }
        ++i;
    }
    new_array[i] = NULL;
    return (new_array);
}
