/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

/* `s` points right after the '%'; returns characters consumed. Unlike
** printf, scanf's width is always a literal number, never `*`-from-args. */
size_t sf_parse_spec(const char *s, t_sf_spec *spec)
{
    size_t i;

    i = 0;
    spec->suppress = false;
    if (s[i] == '*')
    {
        spec->suppress = true;
        ++i;
    }
    spec->has_width = false;
    spec->width = 0;
    while (ft_isdigit(s[i]))
    {
        spec->has_width = true;
        spec->width = spec->width * 10 + (s[i] - '0');
        ++i;
    }
    spec->length = PF_LEN_NONE;
    if (s[i] == 'h' && s[i + 1] == 'h')
    {
        spec->length = PF_LEN_HH;
        i += 2;
    }
    else if (s[i] == 'h')
    {
        spec->length = PF_LEN_H;
        ++i;
    }
    else if (s[i] == 'l' && s[i + 1] == 'l')
    {
        spec->length = PF_LEN_LL;
        i += 2;
    }
    else if (s[i] == 'l')
    {
        spec->length = PF_LEN_L;
        ++i;
    }
    else if (s[i] == 'z')
    {
        spec->length = PF_LEN_Z;
        ++i;
    }
    spec->conv = s[i];
    if (s[i])
        ++i;
    return (i);
}

/* %c and a literal '%' do not skip whitespace; handled by their own
** callers, not here. */
int sf_skip_space(t_sf_src *src)
{
    int c;
    int count;

    count = 0;
    c = sf_getc(src);
    while (c >= 0 && ft_isspace(c))
    {
        ++count;
        c = sf_getc(src);
    }
    if (c >= 0)
        sf_ungetc(src, c);
    return (count);
}
