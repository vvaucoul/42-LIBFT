/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lentc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* index of the first occurrence of `c` in `str`, or 0 if absent */
size_t ft_lentc(const char *str, char c)
{
    size_t i;

    if (!str)
        return (0);
    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        ++i;
    }
    return (0);
}
