/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:56:36 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:15:19 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void ft_bsort(void *array, size_t size, size_t elem_size, CompareFunc compare) {
    char *ptr = (char*)array;
    char *end = (char*)array + (size - 1) * elem_size;
    char tmp[elem_size];
    
    while (ptr < end) {
        if (compare(ptr, ptr + elem_size) > 0) {
            ft_memcpy(tmp, ptr, elem_size);
            ft_memcpy(ptr, ptr + elem_size, elem_size);
            ft_memcpy(ptr + elem_size, tmp, elem_size);
            ptr = (char*)array;
        } else {
            ptr += elem_size;
        }
    }
}