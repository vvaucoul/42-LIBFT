/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_readall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <file.h>
#include <libft.h>

char *file_readall(const char *filename)
{
    int     fd;
    char    *line;
    char    *tmp;

    fd = file_open(filename, O_RDONLY, 0);
    line = NULL;
    while ((tmp = file_readline(fd)) != NULL)
    {
        if (!line)
            line = tmp;
        else
        {
            line = ft_fstrjoin(line, tmp);
            free(tmp);
        }
        line = ft_fstrjoin(line, "\n");
    }
    file_close(fd);
    return (line);
}
