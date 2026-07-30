/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_list_recursive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <file.h>
#include <libft.h>

static size_t   ft_arraylen(char **array)
{
    size_t  i;

    if (!array)
        return (0);
    i = 0;
    while (array[i])
        ++i;
    return (i);
}

static void ft_arrayfree(char **array, size_t size)
{
    size_t  i;

    if (!array)
        return ;
    i = 0;
    while (i < size)
    {
        free(array[i]);
        ++i;
    }
    free(array);
}

static void merge_sub_entries(char ***filenames, size_t *count,
        const char *entry_name, char **sub_filenames)
{
    size_t  i;
    char    *prefix;

    i = 0;
    while (sub_filenames && sub_filenames[i])
    {
        prefix = ft_strjoin(entry_name, "/");
        *filenames = ft_realloc(*filenames, (*count + 2) * sizeof(char *));
        (*filenames)[*count] = ft_fstrjoin(prefix, sub_filenames[i]);
        ++(*count);
        (*filenames)[*count] = NULL;
        ++i;
    }
}

char **dir_list_recursive(const char *dirname)
{
    DIR             *dir;
    struct dirent   *entry;
    char            **filenames;
    char            *path;
    char            **sub_filenames;
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
        if (entry->d_type == DT_DIR)
        {
            path = ft_strjoin(dirname, "/");
            path = ft_fstrjoin(path, entry->d_name);
            sub_filenames = dir_list_recursive(path);
            free(path);
            merge_sub_entries(&filenames, &count, entry->d_name,
                sub_filenames);
            ft_arrayfree(sub_filenames, ft_arraylen(sub_filenames));
        }
    }
    closedir(dir);
    return (filenames);
}
