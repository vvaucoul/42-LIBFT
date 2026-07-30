/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* find the first occurrence of `c` in `str` (c == '\0' matches the
** string's own terminator, like the standard strchr()) */
char *ft_strchr(const char *str, int c)
{
    size_t i;

    if (!str)
        return (NULL);
    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return ((char *)str + i);
        ++i;
    }
    if (!c)
        return ((char *)str + i);
    return (NULL);
}
