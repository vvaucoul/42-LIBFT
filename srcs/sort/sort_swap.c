/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_internal.h"

/* `swap_buf` is caller-allocated and reused across every swap to avoid a
** malloc/free pair per swap. */
void sort_swap(char *a, char *b, size_t elem_size, char *swap_buf)
{
    if (a == b)
        return ;
    ft_memcpy(swap_buf, a, elem_size);
    ft_memcpy(a, b, elem_size);
    ft_memcpy(b, swap_buf, elem_size);
}
