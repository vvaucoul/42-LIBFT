/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Digit value for base 2-16 ('0'-'9', 'a'-'f'/'A'-'F'); -1 if invalid. */
static int base_digit_value(char c)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
    if (c >= 'a' && c <= 'f')
        return (c - 'a' + 10);
    if (c >= 'A' && c <= 'F')
        return (c - 'A' + 10);
    return (-1);
}

int ft_atoi_base(const char *str, int base)
{
    int result;
    bool is_neg;
    int digit;
    size_t i;

    if (!str || base < 2 || base > 16)
        return (0);
    i = 0;
    while (ft_isspace(str[i]))
        ++i;
    is_neg = false;
    if (str[i] == '-' || str[i] == '+')
    {
        is_neg = (str[i] == '-');
        ++i;
    }
    result = 0;
    while ((digit = base_digit_value(str[i])) >= 0 && digit < base)
    {
        result = result * base + digit;
        ++i;
    }
    return (is_neg ? -result : result);
}
