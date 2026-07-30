/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <file.h>
#include <libft.h>

void file_copy(const char *src_filename, const char *dst_filename)
{
    int     src_fd;
    int     dst_fd;
    char    *line;

    src_fd = file_open(src_filename, O_RDONLY, 0);
    dst_fd = file_open(dst_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while ((line = file_readline(src_fd)) != NULL)
    {
        file_writeline(dst_fd, line);
        file_writeline(dst_fd, "\n");
        free(line);
    }
    file_close(src_fd);
    file_close(dst_fd);
}
