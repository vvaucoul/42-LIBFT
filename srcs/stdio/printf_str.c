/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

/* NULL prints as "(null)", matching glibc. */
void pf_format_str(t_pf_sink *sink, t_pf_spec *spec, const char *str)
{
    size_t  len;
    size_t  pad;

    if (!str)
        str = "(null)";
    len = ft_strlen(str);
    if (spec->has_precision && (size_t)spec->precision < len)
        len = (size_t)spec->precision;
    pad = 0;
    if (spec->width > 0 && (size_t)spec->width > len)
        pad = (size_t)spec->width - len;
    if (!spec->left_align)
        pf_write_padding(sink, ' ', pad);
    pf_sink_write(sink, str, len);
    if (spec->left_align)
        pf_write_padding(sink, ' ', pad);
}

/* Precision has no defined effect on %c (C standard, 7.21.6.1) - only
** width/justification apply. */
void pf_format_char(t_pf_sink *sink, t_pf_spec *spec, char c)
{
    size_t  pad;

    pad = 0;
    if (spec->width > 0 && (size_t)spec->width > 1)
        pad = (size_t)spec->width - 1;
    if (!spec->left_align)
        pf_write_padding(sink, ' ', pad);
    pf_sink_write(sink, &c, 1);
    if (spec->left_align)
        pf_write_padding(sink, ' ', pad);
}

/* NULL prints as "(nil)"; the "0x" prefix is forced on unconditionally
** (real %p always shows it, unlike %x). */
void pf_format_ptr(t_pf_sink *sink, t_pf_spec *spec, void *ptr)
{
    t_pf_spec   ptr_spec;

    if (!ptr)
    {
        pf_format_str(sink, spec, "(nil)");
        return ;
    }
    ptr_spec = *spec;
    ptr_spec.alt_form = true;
    ptr_spec.has_precision = false;
    pf_format_int(sink, &ptr_spec, (unsigned long long)(uintptr_t)ptr,
        false, 16, false);
}
