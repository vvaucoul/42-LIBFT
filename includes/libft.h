/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:56:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 15:18:54 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "ft_printf.h"

typedef enum
{
    false,
    true
} bool;

/******************************************************************************/
/*							         ARRAY           		                  */
/******************************************************************************/

// - FT [Array Contain One Of] -> Check if array contain str
bool ft_acof(const char **array, const char *str);
size_t ft_asize(const char **array);
size_t ft_alen(const char **array);

/******************************************************************************/
/*							         ALLOC           		                  */
/******************************************************************************/

void *ft_calloc(size_t size, size_t count);
void ft_multifree(void **ptrs);

/******************************************************************************/
/*							         MEMORY           		                  */
/******************************************************************************/

void *ft_memset(void *ptr, int c, size_t len);
void *ft_memcpy(void *dst, const void *restrict src, size_t len);
void *ft_bzero(void *ptr, size_t len);
void *ft_memlower(void *ptr, size_t len);
void *ft_memupper(void *ptr, size_t len);
void *ft_memcrm(void *ptr, char c, size_t len);
void *ft_memsrm(void *ptr, char *str, size_t len);
int ft_memcmp(const void *ptr, const void *ptr_cmp, size_t len);
int ft_memscmp(const void *ptr, const void *ptr_cmp, size_t len, size_t start);
void *ft_memchr(const void *ptr, int value, size_t len);
void *ft_memshr(const void *ptr, const void *cmp, size_t len, size_t nb);
void *ft_memalloc(void **dst, const void *ref, size_t size, size_t len);
void *ft_memmove(void *dest, const void *ptr, size_t len);

void ft_swap(int *ptr, int *ptr_swap);
void ft_vswap(void **ptr, void **ptr2);

/******************************************************************************/
/*							          CHAR           		                  */
/******************************************************************************/

// - FT [Char Contain One Of] => Char contain one of char in str
bool ft_ccof(char c, const char *str);

bool ft_isascii(int c);
bool ft_isalpha(int c);
bool ft_isalnum(int c);
bool ft_isdigit(int c);
bool ft_isupper(int c);
bool ft_islower(int c);
bool ft_isspace(int c);

int ft_toupper(int c);
int ft_tolower(int c);

/******************************************************************************/
/*							        STRINGS           		                  */
/******************************************************************************/

// - FT [String Contain One Of] => String contain one of char in str
bool ft_scof(char *str, const char *cmp);
bool ft_sncof(char *str, const char *cmp, size_t len);

char *ft_strdup(const char *str);
size_t ft_strlen(const char *str);
int ft_strcmp(const char *str, const char *str2);
char *ft_strcpy(const char *str);
char *ft_strncpy(const char *str, size_t len);
char *ft_strchr(const char *str, int c);
char *ft_strjoin(const char *str, const char *join);
char *ft_fstrjoin(char *str, const char *join);
char *ft_strcjoin(char *str, char c);
char *ft_fstrcjoin(char *str, char c);
char *ft_multijoin(const char **array);
int ft_strsncmp(const char *str, const char *cmp, size_t start, size_t len);
char *ft_strtrim(char *str);
char *ft_strzap(char *str, const char *pat);
char *ft_strsplit(char *src, char **words, const char *sep);
char *ft_strremove(const char *str, char c);

// FT - [STR Remove Doublons] -> Remove doublons in string str
char *ft_strrdbls(const char *str, char c);

/******************************************************************************/
/*							        NUMBERS           		                  */
/******************************************************************************/

size_t ft_nbrlen(int nbr);

/******************************************************************************/
/*							         PRINT           		                  */
/******************************************************************************/

void ft_putchar(char c);
void ft_putendl(const char *str);
void ft_putstr(const char *str);
void ft_putnbr(int nbr);

#endif