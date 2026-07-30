/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

#define SF_FLOAT_BUF 64

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

/* Digits beyond the buffer's capacity are still consumed from the input
** but silently dropped from the value passed to ft_atof(). */
static void capture(char *buf, size_t *len, int c)
{
    if (*len < SF_FLOAT_BUF - 1)
        buf[(*len)++] = (char)c;
}

static bool scan_digit_run(t_sf_src *src, size_t *budget, char *buf,
        size_t *len)
{
    int     c;
    bool    any;

    any = false;
    c = budget_getc(src, budget);
    while (c >= 0 && ft_isdigit(c))
    {
        capture(buf, len, c);
        any = true;
        c = budget_getc(src, budget);
    }
    budget_ungetc(src, budget, c);
    return (any);
}

/* If no digit follows the exponent marker/sign, everything read for the
** attempt is pushed back so the number ends cleanly right before it. */
static void scan_exponent(t_sf_src *src, size_t *budget, char *buf,
        size_t *len)
{
    int marker;
    int sign_c;
    int first_digit;

    marker = budget_getc(src, budget);
    if (marker != 'e' && marker != 'E')
    {
        budget_ungetc(src, budget, marker);
        return ;
    }
    sign_c = budget_getc(src, budget);
    if (sign_c != '+' && sign_c != '-')
    {
        budget_ungetc(src, budget, sign_c);
        sign_c = -1;
    }
    first_digit = budget_getc(src, budget);
    if (!ft_isdigit(first_digit))
    {
        budget_ungetc(src, budget, first_digit);
        if (sign_c >= 0)
            budget_ungetc(src, budget, sign_c);
        budget_ungetc(src, budget, marker);
        return ;
    }
    capture(buf, len, marker);
    if (sign_c >= 0)
        capture(buf, len, sign_c);
    capture(buf, len, first_digit);
    scan_digit_run(src, budget, buf, len);
}

bool sf_scan_float(t_sf_src *src, t_sf_spec *spec, va_list args)
{
    char    buf[SF_FLOAT_BUF];
    size_t  len;
    size_t  budget;
    int     c;
    bool    any_digits;
    double  value;

    sf_skip_space(src);
    budget = spec->has_width ? (size_t)spec->width : (size_t)-1;
    len = 0;
    c = budget_getc(src, &budget);
    if (c == '+' || c == '-')
        capture(buf, &len, c);
    else
        budget_ungetc(src, &budget, c);
    any_digits = scan_digit_run(src, &budget, buf, &len);
    c = budget_getc(src, &budget);
    if (c == '.')
    {
        capture(buf, &len, c);
        if (scan_digit_run(src, &budget, buf, &len))
            any_digits = true;
    }
    else
        budget_ungetc(src, &budget, c);
    if (!any_digits)
        return (false);
    scan_exponent(src, &budget, buf, &len);
    buf[len] = '\0';
    value = ft_atof(buf);
    if (spec->suppress)
        return (true);
    if (spec->length == PF_LEN_L)
        *va_arg(args, double *) = value;
    else
        *va_arg(args, float *) = (float)value;
    return (true);
}
