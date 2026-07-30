/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lents.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* get the index of the first occurrence of `cmp` in `str`, or
** ft_strlen(str) if it never occurs */
size_t ft_lents(const char *str, const char *cmp)
{
    size_t len;
    size_t i;

    if (!str || !cmp)
        return (0);
    len = ft_strlen(cmp);
    i = 0;
    while (str[i])
    {
        if (!ft_strncmp(&str[i], cmp, len))
            return (i);
        ++i;
    }
    return (ft_strlen(str));
}
