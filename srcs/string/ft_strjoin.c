/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* NULL `str` returns NULL; NULL `join` returns `str` unchanged. */
char *ft_strjoin(const char *str, const char *join)
{
    char    *new_str;
    size_t  i;
    size_t  j;
    size_t  length;

    if (!str)
        return (NULL);
    if (!join)
        return ((char *)str);
    length = ft_strlen(str) + ft_strlen(join) + 1;
    if (!(new_str = ft_calloc(sizeof(char), length)))
        return (NULL);
    i = 0;
    while (str[i])
    {
        new_str[i] = str[i];
        ++i;
    }
    j = 0;
    while (join[j])
    {
        new_str[i + j] = join[j];
        ++j;
    }
    return (new_str);
}
