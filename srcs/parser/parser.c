/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 10:04:45 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/10 10:40:46 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>

static void add_arg_back(Parser *__parser, ParserArg *__arg)
{
    if (__parser->root == NULL)
        __parser->root = __arg;
    else
    {
        ParserArg *__tmp = __parser->root;
        while (__tmp->next != NULL)
            __tmp = __tmp->next;
        __tmp->next = __arg;
    }
}

static ParserArg *create_new_element(const char *str, size_t index)
{
    ParserArg *new_arg = NULL;

    if (!(new_arg = malloc(sizeof(ParserArg) * 1)))
        return (NULL);
    new_arg->str = ft_strdup(str);
    new_arg->index = index;
    new_arg->next = NULL;
    return (new_arg);
}

Parser *ft_parser(int argc, const char **argv)
{
    Parser *__parser;

    if (!(__parser = malloc(sizeof(Parser) * 1)))
        return (NULL);
    __parser->nb_args = argc - 1;
    __parser->root = NULL;

    for (size_t i = 0; i < __parser->nb_args + 1; ++i)
    {
        ParserArg *__arg = create_new_element(argv[i + 1], i);
        add_arg_back(__parser, __arg);
    }
    return (__parser);
}

void ft_free_parser(Parser **restrict __parser)
{
    if (!__parser || !(*__parser))
        return;
    ParserArg *__tmp = (*__parser)->root;
    while (__tmp)
    {
        ParserArg *__tmp2 = __tmp;
        __tmp = __tmp->next;
        free((char *)__tmp2->str);
        free(__tmp2);
    }
    free(*__parser);
}