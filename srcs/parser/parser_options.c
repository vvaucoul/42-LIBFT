/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

/* All-or-nothing: on allocation failure the parser's state is left exactly
** as it was before the call. */
bool parser_add_option(Parser *parser, char short_name, const char *long_name,
        t_parser_opt_type type, const char *description, bool required)
{
    t_parser_option     *option;
    t_parser_option     **grown_options;
    t_parser_option     **grown_long_index;
    char                *long_name_copy;
    char                *description_copy;
    size_t              insert_at;

    if (!parser || (short_name == '\0' && !long_name))
        return (false);
    if (short_name != '\0' && parser_find_short(parser, short_name))
        return (false);
    if (long_name && parser_find_long(parser, long_name))
        return (false);
    long_name_copy = long_name ? ft_strdup(long_name) : NULL;
    if (long_name && !long_name_copy)
        return (false);
    description_copy = description ? ft_strdup(description) : NULL;
    if (description && !description_copy)
        return (free(long_name_copy), false);
    grown_options = parser_grow(parser->options, &parser->options_capacity,
            sizeof(t_parser_option *), parser->options_count + 1);
    if (!grown_options)
        return (free(long_name_copy), free(description_copy), false);
    parser->options = grown_options;
    grown_long_index = parser->long_index;
    if (long_name_copy)
    {
        grown_long_index = parser_grow(parser->long_index,
                &parser->long_index_capacity, sizeof(t_parser_option *),
                parser->long_index_count + 1);
        if (!grown_long_index)
            return (free(long_name_copy), free(description_copy), false);
        parser->long_index = grown_long_index;
    }
    if (!(option = malloc(sizeof(t_parser_option))))
        return (free(long_name_copy), free(description_copy), false);
    option->short_name = short_name;
    option->long_name = long_name_copy;
    option->type = type;
    option->description = description_copy;
    option->required = required;
    option->is_set = false;
    option->bool_value = false;
    option->string_value = NULL;
    option->int_value = 0;
    parser->options[parser->options_count++] = option;
    if (short_name != '\0')
        parser->short_index[(unsigned char)short_name] = option;
    if (long_name_copy)
    {
        insert_at = parser->long_index_count;
        while (insert_at > 0 && ft_strcmp(
                parser->long_index[insert_at - 1]->long_name,
                option->long_name) > 0)
        {
            parser->long_index[insert_at] = parser->long_index[insert_at - 1];
            --insert_at;
        }
        parser->long_index[insert_at] = option;
        ++parser->long_index_count;
    }
    return (true);
}

bool parser_get_flag(Parser *parser, const char *long_name)
{
    t_parser_option *option;

    option = parser_find_long(parser, long_name);
    if (!option)
        return (false);
    return (option->bool_value);
}

const char *parser_get_string(Parser *parser, const char *long_name,
        const char *default_value)
{
    t_parser_option *option;

    option = parser_find_long(parser, long_name);
    if (!option || !option->is_set)
        return (default_value);
    return (option->string_value);
}

long parser_get_int(Parser *parser, const char *long_name, long default_value)
{
    t_parser_option *option;

    option = parser_find_long(parser, long_name);
    if (!option || !option->is_set)
        return (default_value);
    return (option->int_value);
}

bool parser_is_set(Parser *parser, const char *long_name)
{
    t_parser_option *option;

    option = parser_find_long(parser, long_name);
    if (!option)
        return (false);
    return (option->is_set);
}

size_t parser_positional_count(Parser *parser)
{
    if (!parser)
        return (0);
    return (parser->positional_count);
}

const char *parser_get_positional(Parser *parser, size_t index)
{
    if (!parser || index >= parser->positional_count)
        return (NULL);
    return (parser->positional[index]);
}

bool parser_has_error(Parser *parser)
{
    if (!parser)
        return (false);
    return (parser->has_error);
}

const char *parser_error_message(Parser *parser)
{
    if (!parser)
        return ("");
    return (parser->error);
}
