/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Like ft_nbrlen() but for `long`; never negates `nbr`, so LONG_MIN
** is safe. */
size_t ft_nbrlen_long(long nbr)
{
    size_t n;

    n = 1;
    while (nbr / 10)
    {
        nbr /= 10;
        ++n;
    }
    return (n);
}
