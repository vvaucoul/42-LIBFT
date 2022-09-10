/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 10:05:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/10 10:40:44 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "libft.h"

typedef struct s_parser_arg
{
    const char *str;
    size_t index;
    struct s_parser_arg *next;
} t_parser_arg;

typedef struct s_parser
{
    size_t nb_args;
    t_parser_arg *root;
} t_parser;

#define Parser t_parser
#define ParserArg t_parser_arg

extern Parser *ft_parser(int argc, const char **argv);
extern void ft_free_parser(Parser **restrict __parser);

#define ForEachArgs(parser) for (ParserArg *restrict arg = parser->root; arg->next != NULL; arg = arg->next)

#endif /* PARSER_H */