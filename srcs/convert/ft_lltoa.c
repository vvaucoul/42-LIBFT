/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

/* Magnitude computed in unsigned arithmetic to avoid overflow when
** negating LLONG_MIN. */
static unsigned long long ll_magnitude(long long n)
{
    if (n == LLONG_MIN)
        return (9223372036854775808ULL);
    if (n < 0)
        return ((unsigned long long)(-n));
    return ((unsigned long long)n);
}

static size_t ll_magnitude_len(unsigned long long magnitude)
{
    size_t len;

    if (magnitude == 0)
        return (1);
    len = 0;
    while (magnitude)
    {
        magnitude /= 10;
        ++len;
    }
    return (len);
}

char *ft_lltoa(long long n)
{
    unsigned long long magnitude;
    size_t len;
    size_t pos;
    char *str;
    int is_neg;

    is_neg = (n < 0);
    magnitude = ll_magnitude(n);
    len = ll_magnitude_len(magnitude);
    if (!(str = malloc(len + is_neg + 1)))
        return (NULL);
    pos = len + is_neg;
    str[pos] = '\0';
    if (magnitude == 0)
        str[--pos] = '0';
    while (magnitude)
    {
        str[--pos] = (magnitude % 10) + '0';
        magnitude /= 10;
    }
    if (is_neg)
        str[0] = '-';
    return (str);
}
