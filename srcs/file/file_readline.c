/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <file.h>
#include <libft.h>

/* Returns NULL only when nothing was read at all; a blank line still
** yields an empty (non-NULL) string. */
char *file_readline(int fd)
{
    char    *line;
    char    *tmp;
    size_t  cap;
    char    c;
    int     i;
    int     ret;

    line = NULL;
    cap = 0;
    i = 0;
    while ((ret = read(fd, &c, 1)) > 0 && c != '\n')
    {
        if ((size_t)i + 1 > cap)
        {
            cap = (cap == 0) ? 16 : cap * 2;
            if (!(tmp = ft_realloc(line, cap)))
            {
                free(line);
                return (NULL);
            }
            line = tmp;
        }
        line[i++] = c;
    }
    if (ret == -1)
    {
        free(line);
        fprintf(stderr, "Error: cannot read file descriptor %d\n", fd);
        exit(EXIT_FAILURE);
    }
    if (ret == 0 && i == 0)
        return (NULL);
    if (!(tmp = ft_realloc(line, (size_t)i + 1)))
    {
        free(line);
        return (NULL);
    }
    line = tmp;
    line[i] = '\0';
    return (line);
}
