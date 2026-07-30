/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "libft.h"

/*
** Raw argument view: ForEachArgs() indexes directly into the caller's own
** argv - no copying, no linked list, no allocation.
** Usage: `ForEachArgs(p) { ... arg->str ... }`.
*/
typedef struct s_parser_arg
{
    const char              *str;
    size_t                  index;
    struct s_parser_arg    *next;
}   t_parser_arg;

#define ParserArg t_parser_arg

/*
** CLI argument parser: register options (short `-x`, long `--xxxx`, or
** both), parse them out of argv with getopt-like semantics (combined
** short flags, `--long=value` and `--long value` forms, a `--`
** end-of-options sentinel), read back typed values, list leftover
** positional arguments, and print a generated usage string - all without
** ever calling exit() on a bad argument.
**
** Performance: short-option lookup is a direct O(1) index into a 128-slot
** table (one entry per possible `char`); long-option lookup is O(log n)
** binary search over an array kept sorted by name as options are
** registered.
*/
typedef enum e_parser_opt_type
{
    PARSER_OPT_FLAG,
    PARSER_OPT_STRING,
    PARSER_OPT_INT
}   t_parser_opt_type;

typedef struct s_parser_option
{
    char                short_name;
    char                *long_name;
    t_parser_opt_type   type;
    char                *description;
    bool                required;
    bool                is_set;
    bool                bool_value;
    char                *string_value;
    long                int_value;
}   t_parser_option;

#define ParserOption t_parser_option

typedef struct s_parser
{
    int                 argc;
    const char          **argv;
    size_t              nb_args;

    t_parser_option     **options;
    size_t              options_count;
    size_t              options_capacity;
    t_parser_option     *short_index[128];
    t_parser_option     **long_index;
    size_t              long_index_count;
    size_t              long_index_capacity;

    char                **positional;
    size_t              positional_count;
    size_t              positional_capacity;

    bool                has_error;
    char                error[256];
}   t_parser;

#define Parser t_parser

Parser  *ft_parser(int argc, const char **argv);
void    ft_free_parser(Parser **restrict parser);

#define ForEachArgs(parser) \
    for (size_t _pfe_i = 0; _pfe_i < (parser)->nb_args; ++_pfe_i) \
        for (ParserArg _pfe_arg = { \
                (parser)->argv[_pfe_i + 1], _pfe_i, NULL }, \
            *arg = &_pfe_arg; arg; arg = NULL)

/* Registration - call before parser_parse(). short_name is '\0' for none,
** long_name is NULL for none (at least one of the two must be given). */
bool    parser_add_option(Parser *parser, char short_name,
            const char *long_name, t_parser_opt_type type,
            const char *description, bool required);

/* Parses argv against the registered options. Returns false and sets an
** error message (see parser_error_message()) on the first unknown option,
** missing value, invalid integer, or missing required option. */
bool    parser_parse(Parser *parser);

bool        parser_get_flag(Parser *parser, const char *long_name);
const char  *parser_get_string(Parser *parser, const char *long_name,
                const char *default_value);
long        parser_get_int(Parser *parser, const char *long_name,
                long default_value);
bool        parser_is_set(Parser *parser, const char *long_name);

size_t      parser_positional_count(Parser *parser);
const char  *parser_get_positional(Parser *parser, size_t index);

bool        parser_has_error(Parser *parser);
const char  *parser_error_message(Parser *parser);

/* Mallocated usage string built from every registered option's short
** name, long name, type and description, e.g.:
**   Usage: myprog [OPTIONS]
**     -h, --help            Show this help message
**     -o, --output <value>  Output file path
*/
char    *parser_usage_string(Parser *parser, const char *program_name);

#endif /* PARSER_H */
