/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstrcjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* concatenate a char to a string and free str */
char *ft_fstrcjoin(char *str, char c)
{
    char *new_str;
    size_t len;

    if (!str)
    {
        if (!(new_str = ft_calloc(sizeof(char), 2)))
            return (NULL);
        new_str[0] = c;
        return (new_str);
    }
    len = ft_strlen(str);
    if (!(new_str = ft_calloc(sizeof(char), len + 2)))
        return (NULL);
    ft_memcpy(new_str, str, len);
    new_str[len] = c;
    free(str);
    return (new_str);
}
