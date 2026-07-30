/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDIO_INTERNAL_H
#define STDIO_INTERNAL_H

#include <libft.h>
#include <ft_stdio.h>
#include <stdint.h>
#include <limits.h>

/* ========================================================================
** OUTPUT (printf family)
** ===================================================================== */

/* Where formatted output goes: either a fd (write()) or a caller buffer
** (sprintf/snprintf). `written` always tracks the full logical length
** that WOULD have been produced, even past a bounded buffer's capacity -
** matching snprintf()'s own "return value is the length that would have
** been written" contract. */
typedef struct s_pf_sink
{
    int     fd;
    char    *buf;
    size_t  size;
    bool    bounded;
    size_t  written;
}   t_pf_sink;

typedef enum e_pf_len
{
    PF_LEN_NONE,
    PF_LEN_HH,
    PF_LEN_H,
    PF_LEN_L,
    PF_LEN_LL,
    PF_LEN_Z
}   t_pf_len;

typedef struct s_pf_spec
{
    bool        left_align;
    bool        zero_pad;
    bool        force_sign;
    bool        space_sign;
    bool        alt_form;
    int         width;
    bool        has_precision;
    int         precision;
    t_pf_len    length;
    char        conv;
}   t_pf_spec;

t_pf_sink   pf_sink_fd(int fd);
t_pf_sink   pf_sink_buf(char *buf, size_t size, bool bounded);
void        pf_sink_write(t_pf_sink *sink, const char *data, size_t len);
void        pf_sink_finish(t_pf_sink *sink);
void        pf_write_padding(t_pf_sink *sink, char c, size_t count);

int         pf_format(t_pf_sink *sink, const char *fmt, va_list args);
size_t      pf_parse_spec(const char *s, va_list args, t_pf_spec *spec);

size_t      pf_build_digits(char *buf, unsigned long long value, int base,
                bool uppercase);
long long   pf_fetch_int(va_list args, t_pf_len len);
unsigned long long  pf_fetch_uint(va_list args, t_pf_len len);
void        pf_format_int(t_pf_sink *sink, t_pf_spec *spec,
                unsigned long long magnitude, bool negative, int base,
                bool uppercase);
void        pf_format_str(t_pf_sink *sink, t_pf_spec *spec, const char *str);
void        pf_format_char(t_pf_sink *sink, t_pf_spec *spec, char c);
void        pf_format_ptr(t_pf_sink *sink, t_pf_spec *spec, void *ptr);
void        pf_format_float(t_pf_sink *sink, t_pf_spec *spec, double value);

/* ========================================================================
** INPUT (scanf family)
** ===================================================================== */

/* Where input comes from: either a fd (read(), one byte at a time, with
** one-character pushback so a "peeked" byte that turns out not to match
** can be put back) or a plain string with a running position. */
/* 4 pushback slots: the deepest lookahead any conversion needs is %f's
** exponent - "1e+x" must roll all the way back to just "1" if no digit
** follows the sign, un-reading 'e', '+', and 'x' together. */
typedef struct s_sf_src
{
    const char  *str;
    size_t      pos;
    int         fd;
    int         pushback[4];
    int         pushback_count;
}   t_sf_src;

t_sf_src    sf_src_string(const char *str);
t_sf_src    sf_src_fd(int fd);
int         sf_getc(t_sf_src *src);
void        sf_ungetc(t_sf_src *src, int c);

typedef struct s_sf_spec
{
    bool        suppress;
    bool        has_width;
    int         width;
    t_pf_len    length;
    char        conv;
}   t_sf_spec;

int         sf_vscan(t_sf_src *src, const char *fmt, va_list args);

size_t      sf_parse_spec(const char *s, t_sf_spec *spec);
int         sf_skip_space(t_sf_src *src);
bool        sf_scan_int(t_sf_src *src, t_sf_spec *spec, bool auto_base,
                va_list args);
bool        sf_scan_uint(t_sf_src *src, t_sf_spec *spec, int base,
                va_list args);
bool        sf_scan_str(t_sf_src *src, t_sf_spec *spec, va_list args);
bool        sf_scan_char(t_sf_src *src, t_sf_spec *spec, va_list args);
bool        sf_scan_float(t_sf_src *src, t_sf_spec *spec, va_list args);

#endif /* !STDIO_INTERNAL_H */
