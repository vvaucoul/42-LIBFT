/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
#define PARSER_INTERNAL_H

#include <libft.h>
#include <parser.h>

/* Shared helpers used across the parser module's .c files, deliberately
** not exposed in the public parser.h. */

void                *parser_grow(void *array, size_t *capacity,
                        size_t elem_size, size_t needed);
t_parser_option     *parser_find_short(t_parser *parser, char c);
t_parser_option     *parser_find_long(t_parser *parser, const char *name);
void                parser_set_error(t_parser *parser, const char *fmt, ...);
bool                parser_str_to_long(const char *str, long *out);

#endif /* PARSER_INTERNAL_H */
