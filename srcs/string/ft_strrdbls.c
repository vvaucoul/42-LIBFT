/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrdbls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* [STR Remove Doublons] - collapses consecutive runs of `c` down to a
** single occurrence (frees `str`). */
char *ft_strrdbls(const char *str, char c)
{
    char    *new_str;
    size_t  i;
    size_t  j;
    int     pass;

    if (!str)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
        return (NULL);
    i = 0;
    j = 0;
    pass = 0;
    while (str[i])
    {
        if (str[i] != c)
        {
            new_str[j++] = str[i];
            pass = 0;
        }
        else
        {
            if (pass == 0)
                new_str[j++] = str[i];
            ++pass;
        }
        ++i;
    }
    free((char *)str);
    return (new_str);
}
