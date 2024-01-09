/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:50:03 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:18:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int compare_int(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int compare_char(const void *a, const void *b) {
    return *(char*)a - *(char*)b;
}

int compare_str(const void *a, const void *b) {
    return ft_strcmp(*(char**)a, *(char**)b);
}

int compare_double(const void *a, const void *b) {
    return *(double*)a - *(double*)b;
}

int compare_float(const void *a, const void *b) {
    return *(float*)a - *(float*)b;
}

int compare_long(const void *a, const void *b) {
    return *(long*)a - *(long*)b;
}

int compare_ulong(const void *a, const void *b) {
    return *(unsigned long*)a - *(unsigned long*)b;
}

int compare_llong(const void *a, const void *b) {
    return *(long long*)a - *(long long*)b;
}

int compare_ullong(const void *a, const void *b) {
    return *(unsigned long long*)a - *(unsigned long long*)b;
}