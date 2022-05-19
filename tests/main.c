/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:18:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/19 12:40:05 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int main(int argc, char const *argv[])
{
    Vector *v = vector_new(sizeof(int), 1);

    size_t size = vector_size(v);
    printf("size: %zu\n", size);


    int s = 42;
    vector_push_back(v, (int *) &s);
    printf("size: %zu\n", size);
    printf("Element [0]: %d\n", *(int *)vector_at(v, 0));
}
