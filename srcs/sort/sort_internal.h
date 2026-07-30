/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_INTERNAL_H
#define SORT_INTERNAL_H

#include <libft.h>

/*
** Shared, range-based ([lo, hi] inclusive) sort primitives - not part of
** the public API. ft_isort()/ft_hsort() are thin whole-array wrappers
** around sort_insertion_range()/sort_heapsort_range(); ft_qsort()
** (introsort) calls both of them directly as its small-range cutoff and
** its worst-case fallback, so the exact same tested code runs whether
** you call ft_isort() directly or ft_qsort() delegates to it internally.
*/
void    sort_swap(char *a, char *b, size_t elem_size, char *swap_buf);
void    sort_insertion_range(char *arr, size_t lo, size_t hi,
            size_t elem_size, CompareFunc compare, char *key_buf);
void    sort_heapsort_range(char *arr, size_t lo, size_t hi,
            size_t elem_size, CompareFunc compare, char *swap_buf);

#endif /* !SORT_INTERNAL_H */
