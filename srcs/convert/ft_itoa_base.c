/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:30:02 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Magnitude computed in unsigned arithmetic to avoid signed overflow
** when negating INT_MIN. */
static unsigned int int_magnitude(int nb)
{
    if (nb == -2147483648)
        return (2147483648u);
    if (nb < 0)
        return ((unsigned int)(-nb));
    return ((unsigned int)nb);
}

static size_t magnitude_len_base(unsigned int magnitude, unsigned int base)
{
    size_t len;

    if (magnitude == 0)
        return (1);
    len = 0;
    while (magnitude)
    {
        magnitude /= base;
        ++len;
    }
    return (len);
}

char *ft_itoa_base(int nb, int base)
{
    static const char digits[] = "0123456789abcdef";
    unsigned int magnitude;
    size_t len;
    size_t pos;
    char *str;
    int is_neg;

    if (base < 2 || base > 16)
        return (NULL);
    is_neg = (nb < 0);
    magnitude = int_magnitude(nb);
    len = magnitude_len_base(magnitude, (unsigned int)base);
    if (!(str = malloc(len + is_neg + 1)))
        return (NULL);
    pos = len + is_neg;
    str[pos] = '\0';
    if (magnitude == 0)
        str[--pos] = '0';
    while (magnitude)
    {
        str[--pos] = digits[magnitude % (unsigned int)base];
        magnitude /= (unsigned int)base;
    }
    if (is_neg)
        str[0] = '-';
    return (str);
}
