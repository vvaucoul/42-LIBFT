/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_writeall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <file.h>
#include <libft.h>

void file_writeall(const char *filename, const char *content, int flags,
        int mode)
{
    int fd;

    fd = file_open(filename, flags, mode);
    file_writeline(fd, content);
    file_close(fd);
}
