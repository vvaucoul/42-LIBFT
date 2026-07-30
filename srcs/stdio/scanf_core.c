/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

static bool dispatch(t_sf_src *src, t_sf_spec *spec, va_list args)
{
    if (spec->conv == 'c')
        return (sf_scan_char(src, spec, args));
    if (spec->conv == 's')
        return (sf_scan_str(src, spec, args));
    if (spec->conv == 'd')
        return (sf_scan_int(src, spec, false, args));
    if (spec->conv == 'i')
        return (sf_scan_int(src, spec, true, args));
    if (spec->conv == 'u')
        return (sf_scan_uint(src, spec, 10, args));
    if (spec->conv == 'x' || spec->conv == 'X')
        return (sf_scan_uint(src, spec, 16, args));
    if (spec->conv == 'o')
        return (sf_scan_uint(src, spec, 8, args));
    if (spec->conv == 'f')
        return (sf_scan_float(src, spec, args));
    return (false);
}

static int fail(int assigned)
{
    if (assigned == 0)
        return (-1);
    return (assigned);
}

/* A mismatch is an "input failure" (-1, if nothing assigned yet) only
** when the source had nothing left; otherwise it's a matching failure
** and `assigned` is returned as-is. */
static int handle_percent_literal(t_sf_src *src, int assigned)
{
    int c;

    c = sf_getc(src);
    if (c == '%')
        return (INT_MIN);
    if (c < 0)
        return (fail(assigned));
    sf_ungetc(src, c);
    return (assigned);
}

static int handle_literal_char(t_sf_src *src, char expected, int assigned)
{
    int c;

    c = sf_getc(src);
    if (c == (unsigned char)expected)
        return (INT_MIN);
    if (c < 0)
        return (fail(assigned));
    sf_ungetc(src, c);
    return (assigned);
}

/* INT_MIN is an internal-only "keep going" sentinel from the two
** literal-matching helpers above; a real result is always >= -1. */
int sf_vscan(t_sf_src *src, const char *fmt, va_list args)
{
    size_t      i;
    int         assigned;
    t_sf_spec   spec;
    int         c;
    int         literal_result;

    if (!fmt)
        fmt = "";
    i = 0;
    assigned = 0;
    while (fmt[i])
    {
        if (ft_isspace(fmt[i]))
        {
            sf_skip_space(src);
            while (ft_isspace(fmt[i]))
                ++i;
            continue ;
        }
        if (fmt[i] != '%')
        {
            literal_result = handle_literal_char(src, fmt[i], assigned);
            if (literal_result != INT_MIN)
                return (literal_result);
            ++i;
            continue ;
        }
        ++i;
        i += sf_parse_spec(fmt + i, &spec);
        if (spec.conv == '%')
        {
            literal_result = handle_percent_literal(src, assigned);
            if (literal_result != INT_MIN)
                return (literal_result);
            continue ;
        }
        if (spec.conv != 'c')
            sf_skip_space(src);
        c = sf_getc(src);
        if (c < 0)
            return (fail(assigned));
        sf_ungetc(src, c);
        if (!dispatch(src, &spec, args))
            return (assigned);
        if (!spec.suppress)
            ++assigned;
    }
    return (assigned);
}
