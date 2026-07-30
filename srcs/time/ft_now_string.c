/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_now_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* Formats the current local date/time into `buf` (strftime() syntax;
** NULL defaults to "%Y-%m-%d %H:%M:%S"). */
char *ft_now_string(char *buf, size_t size, const char *format)
{
    time_t      now;
    struct tm   *tm_info;

    if (!buf || size == 0)
        return (NULL);
    now = time(NULL);
    tm_info = localtime(&now);
    if (!tm_info)
        return (NULL);
    if (!format)
        format = "%Y-%m-%d %H:%M:%S";
    if (strftime(buf, size, format, tm_info) == 0)
        return (NULL);
    return (buf);
}
