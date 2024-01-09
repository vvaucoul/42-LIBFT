/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:49:29 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:19:39 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int partition(void *array, int low, int high, size_t size, CompareFunc compare) {
    // Initialize random number generator
    srand(time(NULL));

    // Choose a random pivot
    int pivot_index = low + rand() % (high - low + 1);
    char *pivot = (char *)array + pivot_index * size;

    // Swap the pivot with the last element
    ft_sswap(pivot, (char *)array + high * size, size);
    pivot = (char *)array + high * size;

    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (compare((char *)array + j * size, pivot) <= 0) {
            i++; // increment index of smaller element
            ft_sswap((char *)array + i * size, (char *)array + j * size, size);
        }
    }
    ft_sswap((char *)array + (i + 1) * size, (char *)array + high * size, size);
    return (i + 1);
}

void ft_qsort(void *array, int low, int high, size_t size, CompareFunc compare) {
    if (low < high) {
        // pivot is partitioning index, arr[pivot] is now at right place
        int pivot = partition(array, low, high, size, compare);

        // Separately sort elements before partition and after partition
        ft_qsort(array, low, pivot - 1, size, compare);
        ft_qsort(array, pivot + 1, high, size, compare);
    }
}