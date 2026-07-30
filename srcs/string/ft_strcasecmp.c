/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int ft_strcasecmp(const char *str, const char *str2)
{
    size_t  i;
    int     c1;
    int     c2;

    i = 0;
    while (str[i] || str2[i])
    {
        c1 = ft_tolower((unsigned char)str[i]);
        c2 = ft_tolower((unsigned char)str2[i]);
        if (c1 != c2)
            return (c1 - c2);
        ++i;
    }
    return (0);
}
