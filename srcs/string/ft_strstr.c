/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* substring search returning a pointer (unlike ft_lents(), which
** returns an index). */
char *ft_strstr(const char *haystack, const char *needle)
{
    size_t  needle_len;
    size_t  i;

    if (!haystack || !needle)
        return (NULL);
    needle_len = ft_strlen(needle);
    if (needle_len == 0)
        return ((char *)haystack);
    i = 0;
    while (haystack[i])
    {
        if (!ft_strncmp(&haystack[i], needle, needle_len))
            return ((char *)haystack + i);
        ++i;
    }
    return (NULL);
}
