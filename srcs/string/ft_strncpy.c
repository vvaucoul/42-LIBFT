/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* Custom contract (unlike libc strncpy): allocates a fresh `len`-byte
** copy of `str`, or NULL if `str` is shorter than `len`. */
char *ft_strncpy(const char *str, size_t len)
{
    char    *new_str;
    size_t  i;

    if (!str)
        return (NULL);
    if (ft_strlen(str) < len)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), len + 1)))
        return (NULL);
    i = 0;
    while (str[i] && i < len)
    {
        new_str[i] = str[i];
        ++i;
    }
    return (new_str);
}
