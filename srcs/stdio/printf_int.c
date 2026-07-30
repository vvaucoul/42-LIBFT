/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

/* Builds digits of `value` in `base`, least-significant first (buf[0] is
** the ones digit) - caller writes them out back-to-front. */
size_t pf_build_digits(char *buf, unsigned long long value, int base,
        bool uppercase)
{
    static const char   lower[] = "0123456789abcdef";
    static const char   upper[] = "0123456789ABCDEF";
    const char          *digits;
    size_t              len;

    digits = uppercase ? upper : lower;
    len = 0;
    if (value == 0)
    {
        buf[len++] = '0';
        return (len);
    }
    while (value)
    {
        buf[len++] = digits[value % (unsigned int)base];
        value /= (unsigned int)base;
    }
    return (len);
}

long long pf_fetch_int(va_list args, t_pf_len len)
{
    if (len == PF_LEN_LL)
        return (va_arg(args, long long));
    if (len == PF_LEN_L)
        return (va_arg(args, long));
    if (len == PF_LEN_Z)
        return ((long long)va_arg(args, size_t));
    if (len == PF_LEN_HH)
        return ((signed char)va_arg(args, int));
    if (len == PF_LEN_H)
        return ((short)va_arg(args, int));
    return (va_arg(args, int));
}

unsigned long long pf_fetch_uint(va_list args, t_pf_len len)
{
    unsigned long long v;

    if (len == PF_LEN_LL)
        return (va_arg(args, unsigned long long));
    if (len == PF_LEN_L)
        return (va_arg(args, unsigned long));
    if (len == PF_LEN_Z)
        return (va_arg(args, size_t));
    v = va_arg(args, unsigned int);
    if (len == PF_LEN_HH)
        return (v & 0xFFu);
    if (len == PF_LEN_H)
        return (v & 0xFFFFu);
    return (v);
}

static size_t apply_precision_zeros(t_pf_spec *spec, size_t ndigits,
        const char *digits, int base)
{
    size_t nzeros;

    nzeros = 0;
    if (spec->has_precision && (size_t)spec->precision > ndigits)
        nzeros = (size_t)spec->precision - ndigits;
    if (spec->alt_form && base == 8 && nzeros == 0
        && (ndigits == 0 || digits[ndigits - 1] != '0'))
        nzeros = 1;
    return (nzeros);
}

/* d/i/u/x/X/o all funnel through here; a precision of 0 with a value of
** 0 prints no digits at all, per the standard. */
void pf_format_int(t_pf_sink *sink, t_pf_spec *spec,
        unsigned long long magnitude, bool negative, int base,
        bool uppercase)
{
    char        digits[32];
    size_t      ndigits;
    size_t      nzeros;
    const char  *prefix;
    size_t      prefix_len;
    char        sign_char;
    size_t      number_len;
    size_t      pad;

    ndigits = pf_build_digits(digits, magnitude, base, uppercase);
    if (spec->has_precision && spec->precision == 0 && magnitude == 0)
        ndigits = 0;
    nzeros = apply_precision_zeros(spec, ndigits, digits, base);
    sign_char = 0;
    if (negative)
        sign_char = '-';
    else if (spec->force_sign)
        sign_char = '+';
    else if (spec->space_sign)
        sign_char = ' ';
    prefix = "";
    prefix_len = 0;
    if (spec->alt_form && base == 16 && magnitude != 0)
    {
        prefix = uppercase ? "0X" : "0x";
        prefix_len = 2;
    }
    number_len = (sign_char != 0) + prefix_len + nzeros + ndigits;
    pad = 0;
    if (spec->width > 0 && (size_t)spec->width > number_len)
        pad = (size_t)spec->width - number_len;
    if (!spec->left_align && !(spec->zero_pad && !spec->has_precision))
        pf_write_padding(sink, ' ', pad);
    if (sign_char)
        pf_sink_write(sink, &sign_char, 1);
    if (prefix_len)
        pf_sink_write(sink, prefix, prefix_len);
    if (!spec->left_align && spec->zero_pad && !spec->has_precision)
        pf_write_padding(sink, '0', pad);
    pf_write_padding(sink, '0', nzeros);
    while (ndigits > 0)
        pf_sink_write(sink, &digits[--ndigits], 1);
    if (spec->left_align)
        pf_write_padding(sink, ' ', pad);
}
