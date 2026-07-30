/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Unsigned arithmetic avoids the signed overflow of negating INT_MIN. */
static unsigned int nbrlen_base_magnitude(int nbr)
{
    if (nbr == -2147483648)
        return (2147483648u);
    if (nbr < 0)
        return ((unsigned int)(-nbr));
    return ((unsigned int)nbr);
}

/* Digit count of `nbr` in base 2-16, no sign; returns 0 if base is
** out of range. */
size_t ft_nbrlen_base(int nbr, int base)
{
    unsigned int magnitude;
    size_t n;

    if (base < 2 || base > 16)
        return (0);
    magnitude = nbrlen_base_magnitude(nbr);
    n = 1;
    while (magnitude >= (unsigned int)base)
    {
        magnitude /= (unsigned int)base;
        ++n;
    }
    return (n);
}
