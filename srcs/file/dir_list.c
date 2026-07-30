/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <file.h>
#include <libft.h>

char **dir_list(const char *dirname)
{
    DIR             *dir;
    struct dirent   *entry;
    char            **filenames;
    size_t          count;

    dir = opendir(dirname);
    if (!dir)
    {
        fprintf(stderr, "Error: cannot open directory %s\n", dirname);
        exit(EXIT_FAILURE);
    }
    filenames = NULL;
    count = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (ft_strcmp(entry->d_name, ".") == 0
            || ft_strcmp(entry->d_name, "..") == 0)
            continue ;
        filenames = ft_realloc(filenames, (count + 2) * sizeof(char *));
        filenames[count] = ft_strdup(entry->d_name);
        ++count;
        filenames[count] = NULL;
    }
    closedir(dir);
    return (filenames);
}
