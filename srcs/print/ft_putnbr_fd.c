/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void put_uint_fd(unsigned int nbr, int fd)
{
    if (nbr > 9)
        put_uint_fd(nbr / 10, fd);
    ft_putchar_fd((char)(nbr % 10) + '0', fd);
}

void ft_putnbr_fd(int nbr, int fd)
{
    unsigned int magnitude;

    if (nbr < 0)
    {
        ft_putchar_fd('-', fd);
        /* INT_MIN has no positive signed counterpart; use the literal magnitude. */
        if (nbr == -2147483648)
            magnitude = 2147483648u;
        else
            magnitude = (unsigned int)(-nbr);
    }
    else
        magnitude = (unsigned int)nbr;
    put_uint_fd(magnitude, fd);
}
