/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:28:36 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int n_lenght(int n)
{
    int nsize;

    nsize = 0;
    if (n > -2147483648 && n < 0)
    {
        ++nsize;
        n *= -1;
    }
    else if (n == 0)
        return (1);
    while (n >= 1)
    {
        n /= 10;
        ++nsize;
    }
    return (nsize);
}

char *ft_itoa(int n)
{
    int i;
    int size;
    char *str;
    int isneg;

    if (n == -2147483648)
        return (ft_strdup("-2147483648"));
    size = n_lenght(n);
    if (!(str = malloc(sizeof(char) * (size + 1))))
        return (NULL);
    if ((isneg = (n < 0)) == 1)
        n *= -1;
    i = 1;
    while (size - i >= 0)
    {
        str[size - i] = n % 10 + 48;
        n /= 10;
        ++i;
    }
    if (isneg)
        str[0] = '-';
    str[size] = '\0';
    return (str);
}
