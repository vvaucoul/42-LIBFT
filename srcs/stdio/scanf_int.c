/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

/* Width (if given) bounds the TOTAL characters consumed by a conversion
** (sign + prefix + digits together) - a small counter threaded through
** every read/unread during that conversion enforces it. */
static int budget_getc(t_sf_src *src, size_t *budget)
{
    int c;

    if (*budget == 0)
        return (-1);
    c = sf_getc(src);
    if (c >= 0)
        --(*budget);
    return (c);
}

static void budget_ungetc(t_sf_src *src, size_t *budget, int c)
{
    if (c < 0)
        return ;
    sf_ungetc(src, c);
    ++(*budget);
}

static int digit_value(int c)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 10);
    if (c >= 'A' && c <= 'Z')
        return (c - 'A' + 10);
    return (-1);
}

static void store_signed(va_list args, t_pf_len len, long long value)
{
    if (len == PF_LEN_LL)
        *va_arg(args, long long *) = value;
    else if (len == PF_LEN_L)
        *va_arg(args, long *) = (long)value;
    else if (len == PF_LEN_Z)
        *va_arg(args, ssize_t *) = (ssize_t)value;
    else if (len == PF_LEN_HH)
        *va_arg(args, signed char *) = (signed char)value;
    else if (len == PF_LEN_H)
        *va_arg(args, short *) = (short)value;
    else
        *va_arg(args, int *) = (int)value;
}

static void store_unsigned(va_list args, t_pf_len len,
        unsigned long long value)
{
    if (len == PF_LEN_LL)
        *va_arg(args, unsigned long long *) = value;
    else if (len == PF_LEN_L)
        *va_arg(args, unsigned long *) = (unsigned long)value;
    else if (len == PF_LEN_Z)
        *va_arg(args, size_t *) = (size_t)value;
    else if (len == PF_LEN_HH)
        *va_arg(args, unsigned char *) = (unsigned char)value;
    else if (len == PF_LEN_H)
        *va_arg(args, unsigned short *) = (unsigned short)value;
    else
        *va_arg(args, unsigned int *) = (unsigned int)value;
}

static bool read_sign(t_sf_src *src, size_t *budget)
{
    int c;

    c = budget_getc(src, budget);
    if (c == '-')
        return (true);
    if (c != '+')
        budget_ungetc(src, budget, c);
    return (false);
}

/* Detects an optional "0x"/"0X" prefix for base 16, or switches an
** auto-detecting %i to octal on a lone leading '0'. */
static int read_base_prefix(t_sf_src *src, size_t *budget, int base,
        bool auto_base)
{
    int c;
    int c2;

    c = budget_getc(src, budget);
    if (c != '0')
    {
        budget_ungetc(src, budget, c);
        return (base);
    }
    c2 = budget_getc(src, budget);
    if ((base == 16 || auto_base) && (c2 == 'x' || c2 == 'X'))
        return (16);
    budget_ungetc(src, budget, c2);
    budget_ungetc(src, budget, c);
    if (auto_base)
        return (8);
    return (base);
}

static bool read_digits(t_sf_src *src, size_t *budget, int base,
        unsigned long long *out)
{
    int             c;
    int             dv;
    bool            any;
    unsigned long long  value;

    value = 0;
    any = false;
    c = budget_getc(src, budget);
    dv = digit_value(c);
    while (c >= 0 && dv >= 0 && dv < base)
    {
        value = value * (unsigned long long)base + (unsigned long long)dv;
        any = true;
        c = budget_getc(src, budget);
        dv = digit_value(c);
    }
    budget_ungetc(src, budget, c);
    *out = value;
    return (any);
}

/* %d always reads base 10; %i auto-detects hex/octal/decimal from an
** optional "0x" prefix or leading '0'. */
bool sf_scan_int(t_sf_src *src, t_sf_spec *spec, bool auto_base,
        va_list args)
{
    size_t              budget;
    bool                negative;
    int                 base;
    unsigned long long  magnitude;

    sf_skip_space(src);
    budget = spec->has_width ? (size_t)spec->width : (size_t)-1;
    negative = read_sign(src, &budget);
    base = read_base_prefix(src, &budget, 10, auto_base);
    if (!read_digits(src, &budget, base, &magnitude))
        return (false);
    if (!spec->suppress)
    {
        if (negative)
            store_signed(args, spec->length, -(long long)magnitude);
        else
            store_signed(args, spec->length, (long long)magnitude);
    }
    return (true);
}

/* %u/%x/%X/%o still accept an optional sign; a negative value wraps the
** same way assigning a negative int to an unsigned variable would. */
bool sf_scan_uint(t_sf_src *src, t_sf_spec *spec, int base, va_list args)
{
    size_t              budget;
    bool                negative;
    unsigned long long  magnitude;

    sf_skip_space(src);
    budget = spec->has_width ? (size_t)spec->width : (size_t)-1;
    negative = read_sign(src, &budget);
    base = read_base_prefix(src, &budget, base, false);
    if (!read_digits(src, &budget, base, &magnitude))
        return (false);
    if (!spec->suppress)
    {
        if (negative)
            store_unsigned(args, spec->length, -magnitude);
        else
            store_unsigned(args, spec->length, magnitude);
    }
    return (true);
}
