/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* copies `str` into `dest`, or a fresh allocation if `dest` is NULL */
char *ft_strcpy(char *dest, const char *str)
{
    size_t len;
    size_t i;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    if (!dest && !(dest = ft_calloc(sizeof(char), len + 1)))
        return (NULL);
    i = 0;
    while (str[i])
    {
        dest[i] = str[i];
        ++i;
    }
    dest[len] = '\0';
    return (dest);
}
