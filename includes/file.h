/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:38:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:47:18 by vvaucoul         ###   ########.fr       */
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

// Function to open a file
int file_open(const char *filename, int flags, int mode);

// Function to close a file
void file_close(int fd);

// Function to read a line from a file
char *file_readline(int fd);

// Function to write a line to a file
void file_writeline(int fd, const char *line);

// Function to read the entire file into a string
char *file_readall(const char *filename);

// Function to write a string to a file
void file_writeall(const char *filename, const char *content, int flags, int mode);

// Function to copy a file
void file_copy(const char *src_filename, const char *dst_filename);

// Function to delete a file
void file_delete(const char *filename);

// Function to get the size of a file
long file_size(const char *filename);

// Function to check if a file exists
int file_exists(const char *filename);

// Function to create a directory
void dir_create(const char *dirname);

// Function to delete a directory
void dir_delete(const char *dirname);

// Function to list all files in a directory
char **dir_list(const char *dirname);

// Function to list all files in a directory recursively
char **dir_lit_recursive(const char *dirname);

#endif /* !FILE_H */