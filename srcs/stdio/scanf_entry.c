/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

int ft_vsscanf(const char *str, const char *format, va_list args)
{
    t_sf_src src;

    src = sf_src_string(str);
    return (sf_vscan(&src, format, args));
}

int ft_vscanf(const char *format, va_list args)
{
    t_sf_src src;

    src = sf_src_fd(0);
    return (sf_vscan(&src, format, args));
}

int ft_sscanf(const char *str, const char *format, ...)
{
    va_list args;
    int     ret;

    va_start(args, format);
    ret = ft_vsscanf(str, format, args);
    va_end(args);
    return (ret);
}

int ft_scanf(const char *format, ...)
{
    va_list args;
    int     ret;

    va_start(args, format);
    ret = ft_vscanf(format, args);
    va_end(args);
    return (ret);
}
