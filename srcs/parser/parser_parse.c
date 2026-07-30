/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static char *dup_range(const char *start, size_t len)
{
    char *copy;

    if (!(copy = malloc(len + 1)))
        return (NULL);
    ft_memcpy(copy, start, len);
    copy[len] = '\0';
    return (copy);
}

static bool positional_push(Parser *parser, const char *value)
{
    char **grown;

    grown = parser_grow(parser->positional, &parser->positional_capacity,
            sizeof(char *), parser->positional_count + 1);
    if (!grown)
        return (false);
    parser->positional = grown;
    parser->positional[parser->positional_count++] = (char *)value;
    return (true);
}

static bool apply_value(Parser *parser, t_parser_option *option,
        const char *value)
{
    long parsed;

    if (option->type == PARSER_OPT_STRING)
        option->string_value = (char *)value;
    else
    {
        if (!parser_str_to_long(value, &parsed))
        {
            parser_set_error(parser,
                "invalid integer value for option '%s': \"%s\"",
                option->long_name ? option->long_name : "?", value);
            return (false);
        }
        option->int_value = parsed;
    }
    option->is_set = true;
    return (true);
}

/* Handles `--name`, `--name=value`, or `--name value`; if the value comes
** from the next token, `*i` is bumped so the caller's `++i` skips past it. */
static bool parse_long_option(Parser *parser, const char *token, size_t *i)
{
    const char          *name_start;
    const char          *eq;
    char                *name_copy;
    const char          *lookup_name;
    t_parser_option     *option;
    const char          *value;

    name_start = token + 2;
    eq = ft_strchr(name_start, '=');
    name_copy = NULL;
    lookup_name = name_start;
    if (eq)
    {
        name_copy = dup_range(name_start, (size_t)(eq - name_start));
        lookup_name = name_copy;
    }
    option = lookup_name ? parser_find_long(parser, lookup_name) : NULL;
    if (!option)
    {
        parser_set_error(parser, "unknown option '--%s'",
            lookup_name ? lookup_name : name_start);
        return (free(name_copy), false);
    }
    if (option->type == PARSER_OPT_FLAG)
    {
        if (eq)
        {
            parser_set_error(parser, "option '--%s' does not take a value",
                option->long_name);
            return (free(name_copy), false);
        }
        option->bool_value = true;
        option->is_set = true;
        return (free(name_copy), true);
    }
    if (eq)
        value = eq + 1;
    else if (*i + 2 <= parser->nb_args)
    {
        value = parser->argv[*i + 2];
        ++(*i);
    }
    else
    {
        parser_set_error(parser, "option '--%s' requires a value",
            option->long_name);
        return (free(name_copy), false);
    }
    free(name_copy);
    return (apply_value(parser, option, value));
}

/* Handles `-x`, combined flags `-abc`, or a value-taking short option whose
** value is glued (`-ofile`) or in the next token (`-o file`). */
static bool parse_short_options(Parser *parser, const char *token, size_t *i)
{
    size_t              pos;
    char                c;
    t_parser_option     *option;
    const char          *value;

    pos = 1;
    while (token[pos])
    {
        c = token[pos];
        option = parser_find_short(parser, c);
        if (!option)
        {
            parser_set_error(parser, "unknown option '-%c'", c);
            return (false);
        }
        if (option->type == PARSER_OPT_FLAG)
        {
            option->bool_value = true;
            option->is_set = true;
            ++pos;
            continue ;
        }
        if (token[pos + 1])
            value = token + pos + 1;
        else if (*i + 2 <= parser->nb_args)
        {
            value = parser->argv[*i + 2];
            ++(*i);
        }
        else
        {
            parser_set_error(parser, "option '-%c' requires a value", c);
            return (false);
        }
        return (apply_value(parser, option, value));
    }
    return (true);
}

static bool check_required(Parser *parser)
{
    size_t              i;
    t_parser_option     *option;

    i = 0;
    while (i < parser->options_count)
    {
        option = parser->options[i];
        if (option->required && !option->is_set)
        {
            if (option->long_name)
                parser_set_error(parser, "missing required option '--%s'",
                    option->long_name);
            else
                parser_set_error(parser, "missing required option '-%c'",
                    option->short_name);
            return (false);
        }
        ++i;
    }
    return (true);
}

bool parser_parse(Parser *parser)
{
    size_t      i;
    const char  *token;
    bool        options_done;

    if (!parser)
        return (false);
    i = 0;
    options_done = false;
    while (i < parser->nb_args)
    {
        token = parser->argv[i + 1];
        if (!options_done && ft_strcmp(token, "--") == 0)
            options_done = true;
        else if (!options_done && token[0] == '-' && token[1] == '-'
            && token[2])
        {
            if (!parse_long_option(parser, token, &i))
                return (false);
        }
        else if (!options_done && token[0] == '-' && token[1] != '\0')
        {
            if (!parse_short_options(parser, token, &i))
                return (false);
        }
        else if (!positional_push(parser, token))
        {
            parser_set_error(parser,
                "out of memory while recording positional argument");
            return (false);
        }
        ++i;
    }
    return (check_required(parser));
}
