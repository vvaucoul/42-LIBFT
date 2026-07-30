/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int ft_strsncmp(const char *str, const char *cmp, size_t start, size_t len)
{
    size_t i;

    if (!len)
        return (0);
    if (!str || !cmp)
        return (0);
    if (start > ft_strlen(str))
        return (0);
    i = start;
    while (str[i] == cmp[i])
    {
        if ((!str[i] && !cmp[i]) || i == len - 1)
            return (0);
        ++i;
    }
    return (str[i] - cmp[i]);
}
