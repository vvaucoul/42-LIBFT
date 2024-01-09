/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:02:23 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:02:28 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int is_sorted(void *array, size_t size, size_t elem_size, CompareFunc compare) {
    char *ptr = (char*)array;
    char *end = (char*)array + (size - 1) * elem_size;
    
    while (ptr < end) {
        if (compare(ptr, ptr + elem_size) > 0) {
            return (0);
        }
        ptr += elem_size;
    }
    return (1);
}