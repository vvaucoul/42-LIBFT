/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:56:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 11:24:12 by vvaucoul         ###   ########.fr       */
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

int ft_toupper(int c);
int ft_tolower(int c);

/******************************************************************************/
/*							        STRINGS           		                  */
/******************************************************************************/

// - FT [String Contain One Of] => String contain one of char in str
bool ft_scof(char *str, const char *cmp);
char *ft_strdup(const char *str);
size_t ft_strlen(const char *str);
int ft_strcmp(const char *str, const char *str2);
char *ft_strcpy(const char *str);
char *ft_strchr(const char *str, int c);

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