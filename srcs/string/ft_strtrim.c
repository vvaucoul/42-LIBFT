/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* trims leading/trailing whitespace in place, returns the same pointer */
char *ft_strtrim(char *str)
{
    size_t start;
    size_t end;
    size_t i;

    if (!str)
        return (NULL);
    start = 0;
    while (str[start] && ft_isspace(str[start]))
        ++start;
    end = ft_strlen(str);
    while (end > start && ft_isspace(str[end - 1]))
        --end;
    i = 0;
    while (start < end)
        str[i++] = str[start++];
    str[i] = '\0';
    return (str);
}
