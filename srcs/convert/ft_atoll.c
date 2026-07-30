/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long ft_atoll(const char *str)
{
    long long result;
    bool is_neg;
    size_t i;

    if (!str)
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
    while (ft_isdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        ++i;
    }
    return (is_neg ? -result : result);
}
