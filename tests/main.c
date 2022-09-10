/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:18:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/10 10:47:26 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>
#include <parser.h>

#include <stdio.h>

int main(int argc, char const *argv[])
{
    Parser *__parser;

    if ((__parser = ft_parser(argc, argv)) == NULL)
        return (1);

    ForEachArgs(__parser)
    {
        char buffer[128];
        printf("\n%zu: %s\n", arg->index, arg->str);

        ft_bzero(buffer, 128);
        
        if (!(sscanf(arg->str, "value:%s", buffer)))
            sscanf(arg->str, "-%s", buffer);
        printf("Buffer: %s\n", buffer);
    }

    ft_free_parser(&__parser);
}
