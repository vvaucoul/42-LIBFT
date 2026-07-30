/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_writeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <file.h>
#include <libft.h>

void file_writeline(int fd, const char *line)
{
    if (write(fd, line, ft_strlen(line)) == -1)
    {
        fprintf(stderr, "Error: cannot write to file descriptor %d\n", fd);
        exit(EXIT_FAILURE);
    }
}
