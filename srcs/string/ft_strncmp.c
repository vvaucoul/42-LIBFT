/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int ft_strncmp(const char *str, const char *str2, size_t len)
{
    size_t i;

    if (len == 0)
        return (0);
    i = 0;
    while (i < len && (unsigned char)str[i] == (unsigned char)str2[i])
    {
        if (((unsigned char)str[i] == 0 && (unsigned char)str2[i] == 0)
            || i == len - 1)
            return (0);
        ++i;
    }
    return ((unsigned char)str[i] - (unsigned char)str2[i]);
}
