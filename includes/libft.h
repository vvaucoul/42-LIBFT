/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:56:52 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 02:20:34 by vvaucoul         ###   ########.fr       */
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

void ft_multifree(void **ptrs);

/******************************************************************************/
/*							         MEMORY           		                  */
/******************************************************************************/

void *ft_memset(void *ptr, int c, size_t len);
void *ft_memcpy(void *dst, const void *restrict src, size_t len);
void *ft_bzero(void *ptr, size_t len);
void *ft_memlower(void *ptr, size_t len);
void *ft_memupper(void *ptr, size_t len);
size_t ft_memlen(const void *ptr);

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

size_t ft_strlen(const char *str);

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