/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:39:55 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:47:40 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <file.h>
#include <libft.h>

int file_open(const char *filename, int flags, int mode) {
    int fd = open(filename, flags, mode);
    if (fd == -1) {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return fd;
}

void file_close(int fd) {
    if (close(fd) == -1) {
        fprintf(stderr, "Error: cannot close file descriptor %d\n", fd);
        exit(EXIT_FAILURE);
    }
}

char *file_readline(int fd) {
    char *line = NULL;
    char c;
    int i = 0;
    int ret;

    while ((ret = read(fd, &c, 1)) > 0 && c != '\n') {
        line = ft_realloc(line, (i + 1) * sizeof(char));
        line[i++] = c;
    }
    if (ret == -1) {
        fprintf(stderr, "Error: cannot read file descriptor %d\n", fd);
        exit(EXIT_FAILURE);
    }
    if (i > 0) {
        line = ft_realloc(line, (i + 1) * sizeof(char));
        line[i] = '\0';
    }
    return line;
}

void file_writeline(int fd, const char *line) {
    if (write(fd, line, ft_strlen(line)) == -1) {
        fprintf(stderr, "Error: cannot write to file descriptor %d\n", fd);
        exit(EXIT_FAILURE);
    }
}

char *file_readall(const char *filename) {
    int fd = file_open(filename, O_RDONLY, 0);
    char *line = NULL;
    char *tmp;

    while ((tmp = file_readline(fd)) != NULL) {
        line = ft_strjoin(line, tmp);
        line = ft_strjoin(line, "\n");
        free(tmp);
    }
    file_close(fd);
    return line;
}

void file_writeall(const char *filename, const char *content, int flags, int mode) {
    int fd = file_open(filename, flags, mode);
    file_writeline(fd, content);
    file_close(fd);
}
void file_copy(const char *src_filename, const char *dst_filename) {
    int src_fd = file_open(src_filename, O_RDONLY, 0);
    int dst_fd = file_open(dst_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char *line;

    while ((line = file_readline(src_fd)) != NULL) {
        file_writeline(dst_fd, line);
        file_writeline(dst_fd, "\n");
        free(line);
    }
    file_close(src_fd);
    file_close(dst_fd);
}

void file_delete(const char *filename) {
    if (unlink(filename) == -1) {
        fprintf(stderr, "Error: cannot delete file %s\n", filename);
        exit(EXIT_FAILURE);
    }
}

long file_size(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == -1) {
        fprintf(stderr, "Error: cannot get file size for %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return st.st_size;
}

int file_exists(const char *filename) {
    return access(filename, F_OK) != -1;
}

void dir_create(const char *dirname) {
    if (mkdir(dirname, 0755) == -1) {
        fprintf(stderr, "Error: cannot create directory %s\n", dirname);
        exit(EXIT_FAILURE);
    }
}

void dir_delete(const char *dirname) {
    if (rmdir(dirname) == -1) {
        fprintf(stderr, "Error: cannot delete directory %s\n", dirname);
        exit(EXIT_FAILURE);
    }
}

static uint32_t ft_arraylen(char **array) {
    uint32_t i = 0;

    while (array[i] != NULL)
        ++i;
    return i;
}

static void ft_arrayfree(char **array, uint32_t size) {
    uint32_t i = 0;

    while (i < size) {
        free(array[i]);
        ++i;
    }
    free(array);
}

char **dir_list(const char *dirname) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        fprintf(stderr, "Error: cannot open directory %s\n", dirname);
        exit(EXIT_FAILURE);
    }

    char **filenames = NULL;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (ft_strcmp(entry->d_name, ".") != 0 && ft_strcmp(entry->d_name, "..") != 0) {
            filenames = ft_realloc(filenames, (ft_arraylen(filenames) + 2) * sizeof(char *));
            filenames[ft_arraylen(filenames) - 1] = ft_strdup(entry->d_name);
            filenames[ft_arraylen(filenames)] = NULL;
        }
    }
    closedir(dir);
    return filenames;
}

char **dir_lit_recursive(const char *dirname) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        fprintf(stderr, "Error: cannot open directory %s\n", dirname);
        exit(EXIT_FAILURE);
    }

    char **filenames = NULL;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (ft_strcmp(entry->d_name, ".") != 0 && ft_strcmp(entry->d_name, "..") != 0) {
            filenames = ft_realloc(filenames, (ft_arraylen(filenames) + 2) * sizeof(char *));
            filenames[ft_arraylen(filenames) - 1] = ft_strdup(entry->d_name);
            filenames[ft_arraylen(filenames)] = NULL;
            if (entry->d_type == DT_DIR) {
                char *path = ft_strjoin(dirname, "/");
                path = ft_strjoin(path, entry->d_name);
                char **sub_filenames = dir_lit_recursive(path);
                for (int i = 0; sub_filenames[i] != NULL; i++) {
                    filenames = ft_realloc(filenames, (ft_arraylen(filenames) + 2) * sizeof(char *));
                    filenames[ft_arraylen(filenames) - 1] = ft_strjoin(entry->d_name, "/");
                    filenames[ft_arraylen(filenames) - 1] = ft_strjoin(filenames[ft_arraylen(filenames) - 1], sub_filenames[i]);
                    filenames[ft_arraylen(filenames)] = NULL;
                }
                free(path);
                ft_arrayfree(sub_filenames, ft_arraylen(sub_filenames));
            }
        }
    }
    closedir(dir);
    return filenames;
}