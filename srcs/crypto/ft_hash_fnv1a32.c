/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_fnv1a32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>

/* FNV-1a, 32-bit variant - fast, simple, non-cryptographic hash. */
uint32_t	ft_hash_fnv1a32(const void *data, size_t len)
{
	const unsigned char	*bytes;
	uint32_t				hash;
	size_t					i;

	bytes = (const unsigned char *)data;
	hash = 2166136261u;
	i = 0;
	while (i < len)
	{
		hash ^= bytes[i];
		hash *= 16777619u;
		++i;
	}
	return (hash);
}
