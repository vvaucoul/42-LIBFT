/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Simple accumulation-based parser (sign, integer, fraction, exponent);
** not a full IEEE-754-precise strtod(). */
double ft_atof(const char *str)
{
    double result;
    double fraction;
    double divisor;
    bool is_neg;
    bool exp_neg;
    int exponent;
    size_t i;

    if (!str)
        return (0.0);
    i = 0;
    while (ft_isspace(str[i]))
        ++i;
    is_neg = false;
    if (str[i] == '-' || str[i] == '+')
    {
        is_neg = (str[i] == '-');
        ++i;
    }
    result = 0.0;
    while (ft_isdigit(str[i]))
        result = result * 10.0 + (str[i++] - '0');
    if (str[i] == '.')
    {
        ++i;
        fraction = 0.0;
        divisor = 1.0;
        while (ft_isdigit(str[i]))
        {
            fraction = fraction * 10.0 + (str[i++] - '0');
            divisor *= 10.0;
        }
        result += fraction / divisor;
    }
    if (str[i] == 'e' || str[i] == 'E')
    {
        ++i;
        exp_neg = false;
        if (str[i] == '-' || str[i] == '+')
        {
            exp_neg = (str[i] == '-');
            ++i;
        }
        exponent = 0;
        while (ft_isdigit(str[i]))
            exponent = exponent * 10 + (str[i++] - '0');
        while (exponent-- > 0)
            result = exp_neg ? result / 10.0 : result * 10.0;
    }
    return (is_neg ? -result : result);
}
