/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:38:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
#define FILE_H

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdint.h>

int file_open(const char *filename, int flags, int mode);
void file_close(int fd);
char *file_readline(int fd);
void file_writeline(int fd, const char *line);
char *file_readall(const char *filename);
void file_writeall(const char *filename, const char *content, int flags, int mode);
void file_copy(const char *src_filename, const char *dst_filename);
void file_delete(const char *filename);
long file_size(const char *filename);
int file_exists(const char *filename);
void dir_create(const char *dirname);
void dir_delete(const char *dirname);
// Lists are NULL-terminated arrays of malloc'd strings; caller frees.
char **dir_list(const char *dirname);
char **dir_list_recursive(const char *dirname);

#endif /* !FILE_H */
