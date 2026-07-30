/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* extracts `len` bytes starting at `start` into a fresh allocation
** (frees `str`); returns `str` unchanged if the range is out of bounds */
char *ft_substr(char *str, size_t start, size_t len)
{
    char    *new_str;
    size_t  i;
    size_t  j;

    if (!str)
        return (NULL);
    if (len > ft_strlen(str) || start > ft_strlen(str))
        return (str);
    if (!(new_str = ft_calloc(sizeof(char), len + 1)))
        return (NULL);
    j = 0;
    i = start;
    while (str[i] && i < start + len)
    {
        new_str[j] = str[i];
        ++j;
        ++i;
    }
    free(str);
    return (new_str);
}
