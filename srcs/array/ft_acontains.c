/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acontains.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:08:50 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

bool ft_acontains(const char **array, const char *str)
{
    if (!array || !str)
        return (false);
    for (size_t i = 0; array[i]; ++i)
    {
        if (!ft_strcmp(array[i], str))
            return (true);
    }
    return (false);
}
