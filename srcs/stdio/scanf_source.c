/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"

/* Common "source" abstraction so the scanf engine can read from a string
** or an fd without knowing which. */
t_sf_src sf_src_string(const char *str)
{
    t_sf_src src;

    src.str = str ? str : "";
    src.pos = 0;
    src.fd = -1;
    src.pushback_count = 0;
    return (src);
}

t_sf_src sf_src_fd(int fd)
{
    t_sf_src src;

    src.str = NULL;
    src.pos = 0;
    src.fd = fd;
    src.pushback_count = 0;
    return (src);
}

/* -1 is the sole EOF signal; no separate "eof" flag to keep in sync. */
int sf_getc(t_sf_src *src)
{
    unsigned char   c;
    ssize_t         n;

    if (src->pushback_count > 0)
        return (src->pushback[--src->pushback_count]);
    if (src->str)
    {
        if (src->str[src->pos] == '\0')
            return (-1);
        return ((unsigned char)src->str[src->pos++]);
    }
    n = read(src->fd, &c, 1);
    if (n <= 0)
        return (-1);
    return (c);
}

/* A string source rewinds `pos`; an fd source has no rewind, so it
** relies on the pushback buffer instead. */
void sf_ungetc(t_sf_src *src, int c)
{
    if (c < 0)
        return ;
    if (src->str)
    {
        --src->pos;
        return ;
    }
    src->pushback[src->pushback_count++] = c;
}
