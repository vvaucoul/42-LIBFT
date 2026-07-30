/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char *ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
    char    *new_str;
    size_t  i;

    if (!str)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
        return (NULL);
    i = 0;
    while (str[i])
    {
        new_str[i] = f(i, str[i]);
        ++i;
    }
    return (new_str);
}
