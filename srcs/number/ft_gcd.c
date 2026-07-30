/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Unsigned arithmetic avoids the signed overflow of negating INT_MIN. */
static unsigned int gcd_magnitude(int nbr)
{
    if (nbr == -2147483648)
        return (2147483648u);
    if (nbr < 0)
        return ((unsigned int)(-nbr));
    return ((unsigned int)nbr);
}

/* Euclidean algorithm; returns `long` since gcd(INT_MIN, 0) == 2^31
** doesn't fit back in an int. */
long ft_gcd(int a, int b)
{
    unsigned int ua;
    unsigned int ub;
    unsigned int tmp;

    ua = gcd_magnitude(a);
    ub = gcd_magnitude(b);
    while (ub != 0)
    {
        tmp = ub;
        ub = ua % ub;
        ua = tmp;
    }
    return ((long)ua);
}
