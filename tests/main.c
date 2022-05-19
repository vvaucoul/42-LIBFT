/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:18:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/19 13:13:21 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int main(int argc, char const *argv[])
{
    Vector *v = vector_new(sizeof(int), 1);

    printf("size: %zu\n", vector_size(v));
    printf("MaxSize: %zu\n", vector_max_size(v));
    printf("Empty: %d\n", vector_empty(v));

    int s = 42, t = 43;
    vector_push_back(v, (int *) &s);

    printf("size: %zu\n", vector_size(v));
    printf("Element [0]: %d\n", *(int *)vector_at(v, 0));
    vector_push_back(v, (int *)&t);
    printf("size: %zu\n", vector_size(v));
    printf("Element [1]: %d\n", *(int *)vector_at(v, 1));

    printf("Element front: %d\n", *(int *)vector_front(v));
    printf("Element back: %d\n", *(int *)vector_back(v));
    printf("Data: %d\n", *(int *)vector_data(v));
    printf("Empty: %d\n", vector_empty(v));

    vector_swap(v, 0, 1);

    printf("Element front: %d\n", *(int *)vector_front(v));
    printf("Element back: %d\n", *(int *)vector_back(v));

    vector_swap_ptrs(v, vector_at(v, 0), vector_at(v, 1));

    printf("Element front: %d\n", *(int *)vector_front(v));
    printf("Element back: %d\n", *(int *)vector_back(v));

    vector_clear(v);
    printf("Empty: %d\n", vector_empty(v));

    for (size_t i = 0; i < 10; i ++)
    {
        printf("Push back %zu\n", i);
        vector_push_back(v, (int *)&i);
        printf("size: %zu\n", vector_size(v));
        printf("Element [%zu]: %d\n", i, *(int *)vector_at(v, i));
    }

    printf("Element front: %d\n", *(int *)vector_front(v));
    printf("Element back: %d\n", *(int *)vector_back(v));

    vector_delete(v);
    exit(0);

}
