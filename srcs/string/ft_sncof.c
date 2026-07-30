/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sncof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* like ft_scof() but only looks at the first `len` bytes of str */
bool ft_sncof(const char *str, const char *cmp, size_t len)
{
    size_t i;
    size_t j;

    if (!str || !cmp)
        return (false);
    i = 0;
    while (str[i] && i < len)
    {
        j = 0;
        while (cmp[j])
        {
            if (str[i] == cmp[j])
                return (true);
            ++j;
        }
        ++i;
    }
    return (false);
}
