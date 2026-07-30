/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <file.h>
#include <libft.h>

void file_close(int fd)
{
    if (close(fd) == -1)
    {
        fprintf(stderr, "Error: cannot close file descriptor %d\n", fd);
        exit(EXIT_FAILURE);
    }
}
