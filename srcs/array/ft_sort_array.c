/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:43:35 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 00:49:19 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

// Define a function pointer type for the comparison function

// Function to sort the array
void sort_array(void *array, size_t size, size_t elem_size, CompareFunc compare) {
    qsort(array, size, elem_size, compare);
}

void ft_reverse_array(void *array, size_t size, size_t elem_size) {
    char *start = (char*)array;
    char *end = (char*)array + (size - 1) * elem_size;
    char tmp[elem_size];

    while (start < end) {
        ft_memcpy(tmp, start, elem_size);
        ft_memcpy(start, end, elem_size);
        ft_memcpy(end, tmp, elem_size);
        start += elem_size;
        end -= elem_size;
    }
}

int ft_max_in_array(void *array, size_t size, size_t elem_size) {
    char *ptr = (char*)array;
    char *max = ptr;
    
    for (size_t i = 1; i < size; ++i) {
        ptr += elem_size;
        if (ft_memcmp(ptr, max, elem_size) > 0) {
            max = ptr;
        }
    }
    
    return *max;
}

int ft_min_in_array(void *array, size_t size, size_t elem_size) {
    char *ptr = (char*)array;
    char *min = ptr;
    
    for (size_t i = 1; i < size; ++i) {
        ptr += elem_size;
        if (ft_memcmp(ptr, min, elem_size) < 0) {
            min = ptr;
        }
    }
    
    return *min;
}