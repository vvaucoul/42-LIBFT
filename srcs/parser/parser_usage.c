/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_usage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

static char *build_option_line(t_parser_option *option)
{
    char *line;

    line = ft_strdup("  ");
    if (option->short_name)
    {
        line = ft_fstrcjoin(line, '-');
        line = ft_fstrcjoin(line, option->short_name);
        if (option->long_name)
            line = ft_fstrjoin(line, ", ");
    }
    if (option->long_name)
    {
        line = ft_fstrjoin(line, "--");
        line = ft_fstrjoin(line, option->long_name);
    }
    if (option->type != PARSER_OPT_FLAG)
        line = ft_fstrjoin(line, " <value>");
    if (option->required)
        line = ft_fstrjoin(line, " (required)");
    if (option->description)
    {
        line = ft_fstrjoin(line, "\t");
        line = ft_fstrjoin(line, option->description);
    }
    line = ft_fstrjoin(line, "\n");
    return (line);
}

/* Builds a mallocated usage string listing every registered option in
** registration order. */
char *parser_usage_string(Parser *parser, const char *program_name)
{
    char    *result;
    char    *line;
    size_t  i;

    if (!parser)
        return (NULL);
    result = ft_strjoin("Usage: ", program_name ? program_name : "program");
    result = ft_fstrjoin(result, " [OPTIONS]\n");
    i = 0;
    while (i < parser->options_count)
    {
        line = build_option_line(parser->options[i]);
        result = ft_fstrjoin(result, line);
        free(line);
        ++i;
    }
    return (result);
}
