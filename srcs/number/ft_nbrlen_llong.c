/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_llong.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Like ft_nbrlen() but for `long long`; never negates, so LLONG_MIN
** is safe. */
size_t ft_nbrlen_llong(long long nbr)
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
