/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_sink.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_internal.h"
#include <errno.h>

t_pf_sink pf_sink_fd(int fd)
{
    t_pf_sink sink;

    sink.fd = fd;
    sink.buf = NULL;
    sink.size = 0;
    sink.bounded = false;
    sink.written = 0;
    return (sink);
}

/* `bounded` distinguishes ft_snprintf() (size enforced) from ft_sprintf()
** (size ignored, unbounded like the real sprintf()). */
t_pf_sink pf_sink_buf(char *buf, size_t size, bool bounded)
{
    t_pf_sink sink;

    sink.fd = -1;
    sink.buf = buf;
    sink.size = size;
    sink.bounded = bounded;
    sink.written = 0;
    return (sink);
}

/* `written` always advances by the full `len`, even past a bounded
** sink's capacity, matching the real snprintf() return-value contract. */
static void pf_write_all(int fd, const char *data, size_t len)
{
    size_t written;
    ssize_t ret;

    written = 0;
    while (written < len)
    {
        ret = write(fd, data + written, len - written);
        if (ret < 0)
        {
            if (errno == EINTR)
                continue;
            return ;
        }
        written += (size_t)ret;
    }
}

void pf_sink_write(t_pf_sink *sink, const char *data, size_t len)
{
    size_t room;
    size_t copyable;

    if (sink->fd >= 0)
    {
        if (len > 0)
            pf_write_all(sink->fd, data, len);
    }
    else if (sink->buf)
    {
        if (!sink->bounded)
            copyable = len;
        else
        {
            room = sink->size > sink->written ? sink->size - sink->written : 0;
            copyable = len < room ? len : room;
        }
        if (copyable > 0)
            ft_memcpy(sink->buf + sink->written, data, copyable);
    }
    sink->written += len;
}

void pf_write_padding(t_pf_sink *sink, char c, size_t count)
{
    char    chunk[64];
    size_t  step;

    if (count == 0)
        return ;
    ft_memset(chunk, c, sizeof(chunk));
    while (count > 0)
    {
        step = count < sizeof(chunk) ? count : sizeof(chunk);
        pf_sink_write(sink, chunk, step);
        count -= step;
    }
}

/* Terminator goes at the last actually-writable byte, since `written`
** may exceed the buffer's real capacity for a bounded sink. */
void pf_sink_finish(t_pf_sink *sink)
{
    size_t end;

    if (!sink->buf)
        return ;
    if (!sink->bounded)
        sink->buf[sink->written] = '\0';
    else if (sink->size > 0)
    {
        end = sink->written < sink->size - 1 ? sink->written : sink->size - 1;
        sink->buf[end] = '\0';
    }
}
