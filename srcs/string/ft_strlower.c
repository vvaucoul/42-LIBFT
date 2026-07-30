/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* in-place lowercase transform; see ft_strupper(). */
char *ft_strlower(char *str)
{
    size_t i;

    if (!str)
        return (NULL);
    i = 0;
    while (str[i])
    {
        str[i] = (char)ft_tolower((unsigned char)str[i]);
        ++i;
    }
    return (str);
}
