/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Uses `i <= nbr / i` instead of `i * i <= nbr` to avoid signed
** overflow when nbr is near INT_MAX. */
bool ft_is_prime(int nbr)
{
    int i;

    if (nbr < 2)
        return (false);
    i = 2;
    while (i <= nbr / i)
    {
        if (nbr % i == 0)
            return (false);
        ++i;
    }
    return (true);
}
