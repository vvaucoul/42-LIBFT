/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

/* References the caller's argv directly (no copy); argv must outlive
** the parser. */
Parser *ft_parser(int argc, const char **argv)
{
    Parser *parser;

    if (argc < 1 || !argv)
        return (NULL);
    if (!(parser = malloc(sizeof(Parser))))
        return (NULL);
    parser->argc = argc;
    parser->argv = argv;
    parser->nb_args = (size_t)(argc - 1);
    parser->options = NULL;
    parser->options_count = 0;
    parser->options_capacity = 0;
    ft_bzero(parser->short_index, sizeof(parser->short_index));
    parser->long_index = NULL;
    parser->long_index_count = 0;
    parser->long_index_capacity = 0;
    parser->positional = NULL;
    parser->positional_count = 0;
    parser->positional_capacity = 0;
    parser->has_error = false;
    parser->error[0] = '\0';
    return (parser);
}

/* `long_name`/`description` are owned copies and freed here; `string_value`
** points into the caller's argv and must NOT be freed. */
void ft_free_parser(Parser **restrict parser)
{
    size_t i;

    if (!parser || !*parser)
        return ;
    i = 0;
    while (i < (*parser)->options_count)
    {
        free((*parser)->options[i]->long_name);
        free((*parser)->options[i]->description);
        free((*parser)->options[i]);
        ++i;
    }
    free((*parser)->options);
    free((*parser)->long_index);
    free((*parser)->positional);
    free(*parser);
    *parser = NULL;
}
