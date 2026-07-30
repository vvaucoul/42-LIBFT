/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

/* Reads non-whitespace up to `width` if given, otherwise unbounded, just
** like the real scanf()'s %s without a width. */
bool sf_scan_str(t_sf_src *src, t_sf_spec *spec, va_list args)
{
    char    *dst;
    size_t  max;
    size_t  i;
    int     c;

    sf_skip_space(src);
    max = spec->has_width ? (size_t)spec->width : (size_t)-1;
    dst = NULL;
    if (!spec->suppress)
        dst = va_arg(args, char *);
    i = 0;
    c = sf_getc(src);
    while (c >= 0 && !ft_isspace(c) && i < max)
    {
        if (dst)
            dst[i] = (char)c;
        ++i;
        c = sf_getc(src);
    }
    if (c >= 0)
        sf_ungetc(src, c);
    if (dst)
        dst[i] = '\0';
    return (i > 0);
}

/* %c does not skip leading whitespace and does not NUL-terminate its
** output, unlike %s. Default width is 1. */
bool sf_scan_char(t_sf_src *src, t_sf_spec *spec, va_list args)
{
    char    *dst;
    size_t  width;
    size_t  i;
    int     c;

    width = spec->has_width ? (size_t)spec->width : 1;
    dst = NULL;
    if (!spec->suppress)
        dst = va_arg(args, char *);
    i = 0;
    while (i < width)
    {
        c = sf_getc(src);
        if (c < 0)
            return (false);
        if (dst)
            dst[i] = (char)c;
        ++i;
    }
    return (true);
}
