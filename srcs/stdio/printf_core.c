/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

/* An unrecognized conversion prints '%' + the char literally and
** consumes no va_arg, so it never desyncs the va_list. */
static void pf_dispatch(t_pf_sink *sink, t_pf_spec *spec, va_list args)
{
    long long   signed_val;

    if (spec->conv == 'd' || spec->conv == 'i')
    {
        signed_val = pf_fetch_int(args, spec->length);
        if (signed_val < 0)
            pf_format_int(sink, spec, -(unsigned long long)signed_val,
                true, 10, false);
        else
            pf_format_int(sink, spec, (unsigned long long)signed_val,
                false, 10, false);
    }
    else if (spec->conv == 'u')
        pf_format_int(sink, spec, pf_fetch_uint(args, spec->length),
            false, 10, false);
    else if (spec->conv == 'x')
        pf_format_int(sink, spec, pf_fetch_uint(args, spec->length),
            false, 16, false);
    else if (spec->conv == 'X')
        pf_format_int(sink, spec, pf_fetch_uint(args, spec->length),
            false, 16, true);
    else if (spec->conv == 'o')
        pf_format_int(sink, spec, pf_fetch_uint(args, spec->length),
            false, 8, false);
    else if (spec->conv == 's')
        pf_format_str(sink, spec, va_arg(args, const char *));
    else if (spec->conv == 'c')
        pf_format_char(sink, spec, (char)va_arg(args, int));
    else if (spec->conv == 'p')
        pf_format_ptr(sink, spec, va_arg(args, void *));
    else if (spec->conv == 'f')
        pf_format_float(sink, spec, va_arg(args, double));
    else if (spec->conv == '%')
        pf_sink_write(sink, "%", 1);
    else
    {
        pf_sink_write(sink, "%", 1);
        if (spec->conv)
            pf_sink_write(sink, &spec->conv, 1);
    }
}

int pf_format(t_pf_sink *sink, const char *fmt, va_list args)
{
    size_t      i;
    size_t      start;
    t_pf_spec   spec;

    if (!fmt)
        fmt = "";
    i = 0;
    while (fmt[i])
    {
        start = i;
        while (fmt[i] && fmt[i] != '%')
            ++i;
        if (i > start)
            pf_sink_write(sink, fmt + start, i - start);
        if (fmt[i] == '%')
        {
            ++i;
            i += pf_parse_spec(fmt + i, args, &spec);
            pf_dispatch(sink, &spec, args);
        }
    }
    pf_sink_finish(sink);
    return ((int)sink->written);
}
