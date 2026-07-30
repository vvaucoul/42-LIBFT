/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

int ft_vprintf(const char *format, va_list args)
{
    t_pf_sink sink;

    sink = pf_sink_fd(1);
    return (pf_format(&sink, format, args));
}

int ft_vdprintf(int fd, const char *format, va_list args)
{
    t_pf_sink sink;

    sink = pf_sink_fd(fd);
    return (pf_format(&sink, format, args));
}

int ft_vsprintf(char *buf, const char *format, va_list args)
{
    t_pf_sink sink;

    sink = pf_sink_buf(buf, 0, false);
    return (pf_format(&sink, format, args));
}

int ft_vsnprintf(char *buf, size_t size, const char *format, va_list args)
{
    t_pf_sink sink;

    sink = pf_sink_buf(buf, size, true);
    return (pf_format(&sink, format, args));
}

int ft_printf(const char *format, ...)
{
    va_list args;
    int     ret;

    va_start(args, format);
    ret = ft_vprintf(format, args);
    va_end(args);
    return (ret);
}

int ft_dprintf(int fd, const char *format, ...)
{
    va_list args;
    int     ret;

    va_start(args, format);
    ret = ft_vdprintf(fd, format, args);
    va_end(args);
    return (ret);
}

int ft_sprintf(char *buf, const char *format, ...)
{
    va_list args;
    int     ret;

    va_start(args, format);
    ret = ft_vsprintf(buf, format, args);
    va_end(args);
    return (ret);
}

int ft_snprintf(char *buf, size_t size, const char *format, ...)
{
    va_list args;
    int     ret;

    va_start(args, format);
    ret = ft_vsnprintf(buf, size, format, args);
    va_end(args);
    return (ret);
}
