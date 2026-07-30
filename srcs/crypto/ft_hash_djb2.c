/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_djb2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>

/* Bernstein's djb2 - fast, simple, non-cryptographic hash (hash tables). */
uint32_t	ft_hash_djb2(const void *data, size_t len)
{
	const unsigned char	*bytes;
	uint32_t				hash;
	size_t					i;

	bytes = (const unsigned char *)data;
	hash = 5381;
	i = 0;
	while (i < len)
	{
		hash = ((hash << 5) + hash) + bytes[i];
		++i;
	}
	return (hash);
}
