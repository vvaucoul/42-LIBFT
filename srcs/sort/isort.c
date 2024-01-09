/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:00:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:15:21 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void ft_isort(void *array, size_t size, size_t elem_size, CompareFunc compare) {
    char *arr = (char *)array;
    for (size_t i = 1; i < size; ++i) {
        size_t j = i;
        while (j > 0 && compare(arr + (j - 1) * elem_size, arr + j * elem_size) > 0) {
            // Swap elements
            char temp[elem_size];
            ft_memcpy(temp, arr + j * elem_size, elem_size);
            ft_memcpy(arr + j * elem_size, arr + (j - 1) * elem_size, elem_size);
            ft_memcpy(arr + (j - 1) * elem_size, temp, elem_size);
            --j;
        }
    }
}