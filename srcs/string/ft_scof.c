/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* [String Contain One Of] - true if str and cmp share any character in
** common (character overlap, not substring containment). */
bool ft_scof(const char *str, const char *cmp)
{
    size_t i;
    size_t j;

    if (!str || !cmp)
        return (false);
    i = 0;
    while (str[i])
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
