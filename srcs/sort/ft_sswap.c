/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:56:47 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:19:44 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void ft_sswap(void *a, void *b, size_t elem_size) {
    char tmp[elem_size];
    
    ft_memcpy(tmp, a, elem_size);
    ft_memcpy(a, b, elem_size);
    ft_memcpy(b, tmp, elem_size);
}