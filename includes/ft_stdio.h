/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDIO_H
#define FT_STDIO_H

#include <stdarg.h>
#include <stddef.h>

/*
** Formatted I/O module covering the same territory as <stdio.h>'s
** printf/scanf family.
**
** printf family - supports flags (- 0 + space #), width (numeric or
** `*`), precision (numeric or `*`), length modifiers (hh h l ll z), and
** conversions d i u x X o s c p % f. Not supported: e/E/g/G/a/A
** (scientific/hex float notation), positional arguments (%1$d), %n.
** %f is accurate for ordinary values but is NOT a correctly-rounded
** dtoa implementation for every possible double.
**
** scanf family - supports the same conversions on the input side
** (d i u x o s c f %), width, length modifiers, `*` (assignment
** suppression), literal text matching, and whitespace skipping with the
** same semantics as the real scanf family (including %c NOT skipping
** leading whitespace and NOT NUL-terminating). Not supported: %[...]
** scanset conversions, %n.
*/

int     ft_printf(const char *format, ...);
int     ft_dprintf(int fd, const char *format, ...);
int     ft_sprintf(char *buf, const char *format, ...);
int     ft_snprintf(char *buf, size_t size, const char *format, ...);

int     ft_vprintf(const char *format, va_list args);
int     ft_vdprintf(int fd, const char *format, va_list args);
int     ft_vsprintf(char *buf, const char *format, va_list args);
int     ft_vsnprintf(char *buf, size_t size, const char *format,
            va_list args);

int     ft_scanf(const char *format, ...);
int     ft_sscanf(const char *str, const char *format, ...);

int     ft_vscanf(const char *format, va_list args);
int     ft_vsscanf(const char *str, const char *format, va_list args);

#endif /* !FT_STDIO_H */
