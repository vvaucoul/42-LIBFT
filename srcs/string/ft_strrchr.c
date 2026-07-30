/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* like ft_strchr() but scans from the end */
char *ft_strrchr(const char *str, int c)
{
    size_t  i;
    size_t  last;
    bool    found;

    if (!str)
        return (NULL);
    i = 0;
    last = 0;
    found = false;
    while (str[i])
    {
        if (str[i] == (char)c)
        {
            last = i;
            found = true;
        }
        ++i;
    }
    if ((char)c == '\0')
        return ((char *)str + i);
    if (found)
        return ((char *)str + last);
    return (NULL);
}
