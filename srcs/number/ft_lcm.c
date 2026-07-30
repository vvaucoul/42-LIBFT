/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lcm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns `long`: (a / gcd) * b can overflow a plain int even when
** `a` and `b` both fit in one. */
long ft_lcm(int a, int b)
{
    long g;
    long result;

    if (a == 0 || b == 0)
        return (0);
    g = ft_gcd(a, b);
    result = ((long)a / g) * (long)b;
    if (result < 0)
        result = -result;
    return (result);
}
