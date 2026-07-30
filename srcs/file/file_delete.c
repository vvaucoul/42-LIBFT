/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <file.h>
#include <libft.h>

void file_delete(const char *filename)
{
    if (unlink(filename) == -1)
    {
        fprintf(stderr, "Error: cannot delete file %s\n", filename);
        exit(EXIT_FAILURE);
    }
}
