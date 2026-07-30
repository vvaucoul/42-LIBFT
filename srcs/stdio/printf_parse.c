/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

static size_t parse_flags(const char *s, t_pf_spec *spec)
{
    size_t i;

    spec->left_align = false;
    spec->zero_pad = false;
    spec->force_sign = false;
    spec->space_sign = false;
    spec->alt_form = false;
    i = 0;
    while (s[i] == '-' || s[i] == '0' || s[i] == '+' || s[i] == ' '
        || s[i] == '#')
    {
        if (s[i] == '-')
            spec->left_align = true;
        else if (s[i] == '0')
            spec->zero_pad = true;
        else if (s[i] == '+')
            spec->force_sign = true;
        else if (s[i] == ' ')
            spec->space_sign = true;
        else
            spec->alt_form = true;
        ++i;
    }
    return (i);
}

/* A negative width from `*` means "left-align with the absolute value",
** exactly like a literal '-' flag would (C standard, 7.21.6.1p5). */
static size_t parse_width(const char *s, va_list args, t_pf_spec *spec)
{
    size_t i;

    i = 0;
    spec->width = 0;
    if (s[i] == '*')
    {
        spec->width = va_arg(args, int);
        ++i;
    }
    else
        while (ft_isdigit(s[i]))
        {
            spec->width = spec->width * 10 + (s[i] - '0');
            ++i;
        }
    if (spec->width < 0)
    {
        spec->left_align = true;
        spec->width = -spec->width;
    }
    return (i);
}

/* A negative precision from `*` means "as if the precision were
** omitted" (same reference as parse_width()). */
static size_t parse_precision(const char *s, va_list args, t_pf_spec *spec)
{
    size_t i;

    i = 0;
    spec->has_precision = false;
    spec->precision = 0;
    if (s[i] != '.')
        return (0);
    ++i;
    spec->has_precision = true;
    if (s[i] == '*')
    {
        spec->precision = va_arg(args, int);
        ++i;
        if (spec->precision < 0)
        {
            spec->has_precision = false;
            spec->precision = 0;
        }
    }
    else
        while (ft_isdigit(s[i]))
        {
            spec->precision = spec->precision * 10 + (s[i] - '0');
            ++i;
        }
    return (i);
}

static size_t parse_length(const char *s, t_pf_spec *spec)
{
    if (s[0] == 'h' && s[1] == 'h')
        return (spec->length = PF_LEN_HH, 2);
    if (s[0] == 'h')
        return (spec->length = PF_LEN_H, 1);
    if (s[0] == 'l' && s[1] == 'l')
        return (spec->length = PF_LEN_LL, 2);
    if (s[0] == 'l')
        return (spec->length = PF_LEN_L, 1);
    if (s[0] == 'z')
        return (spec->length = PF_LEN_Z, 1);
    spec->length = PF_LEN_NONE;
    return (0);
}

/* `s` points right after the '%'; returns characters consumed (not
** counting the '%' itself). */
size_t pf_parse_spec(const char *s, va_list args, t_pf_spec *spec)
{
    size_t i;

    i = parse_flags(s, spec);
    i += parse_width(s + i, args, spec);
    i += parse_precision(s + i, args, spec);
    i += parse_length(s + i, spec);
    spec->conv = s[i];
    if (s[i])
        ++i;
    return (i);
}
