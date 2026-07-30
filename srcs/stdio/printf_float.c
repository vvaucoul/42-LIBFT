/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

static unsigned long long pow10_ull(int exponent)
{
    unsigned long long result;

    result = 1;
    while (exponent-- > 0)
        result *= 10;
    return (result);
}

/* Caps computed fractional digits at 19 (n > 19 would overflow the
** `unsigned long long` scale) - excess precision prints as trailing zeros. */
static int exact_frac_digits(int precision)
{
    if (precision > 19)
        return (19);
    return (precision);
}

/* Not a correctly-rounded dtoa: rounds the fractional part after scaling
** by 10^precision, rather than using a Grisu/Ryu-style algorithm. */
void pf_format_float(t_pf_sink *sink, t_pf_spec *spec, double value)
{
    bool                negative;
    int                 precision;
    int                 exact;
    unsigned long long  int_part;
    unsigned long long  scale;
    unsigned long long  frac_part;
    char                int_digits[32];
    char                frac_digits[32];
    size_t              int_len;
    size_t              i;
    char                sign_char;
    size_t              total_len;
    size_t              pad;

    negative = value < 0;
    if (negative)
        value = -value;
    precision = spec->has_precision ? spec->precision : 6;
    exact = exact_frac_digits(precision);
    int_part = (unsigned long long)value;
    scale = pow10_ull(exact);
    frac_part = (unsigned long long)((value - (double)int_part)
            * (double)scale + 0.5);
    if (frac_part >= scale)
    {
        frac_part -= scale;
        ++int_part;
    }
    int_len = pf_build_digits(int_digits, int_part, 10, false);
    i = 0;
    while (i < (size_t)exact)
    {
        frac_digits[i] = (char)('0' + frac_part % 10);
        frac_part /= 10;
        ++i;
    }
    sign_char = 0;
    if (negative)
        sign_char = '-';
    else if (spec->force_sign)
        sign_char = '+';
    else if (spec->space_sign)
        sign_char = ' ';
    total_len = (sign_char != 0) + int_len;
    if (precision > 0 || spec->alt_form)
        total_len += 1 + (size_t)precision;
    pad = 0;
    if (spec->width > 0 && (size_t)spec->width > total_len)
        pad = (size_t)spec->width - total_len;
    if (!spec->left_align && !spec->zero_pad)
        pf_write_padding(sink, ' ', pad);
    if (sign_char)
        pf_sink_write(sink, &sign_char, 1);
    if (!spec->left_align && spec->zero_pad)
        pf_write_padding(sink, '0', pad);
    while (int_len > 0)
        pf_sink_write(sink, &int_digits[--int_len], 1);
    if (precision > 0 || spec->alt_form)
    {
        pf_sink_write(sink, ".", 1);
        i = (size_t)exact;
        while (i > 0)
            pf_sink_write(sink, &frac_digits[--i], 1);
        if (precision > exact)
            pf_write_padding(sink, '0', (size_t)(precision - exact));
    }
    if (spec->left_align)
        pf_write_padding(sink, ' ', pad);
}
