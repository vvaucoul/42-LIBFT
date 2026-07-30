/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crc32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>

/* Standard CRC-32 (IEEE 802.3, poly 0xEDB88320), bit-by-bit, no lookup table.
** ft_crc32("123456789", 9) == 0xCBF43926 is the well-known check value. */
static uint32_t	crc32_process_byte(uint32_t value)
{
	uint32_t	crc;
	int			bit;

	crc = value;
	bit = 0;
	while (bit < 8)
	{
		if (crc & 1)
			crc = (crc >> 1) ^ 0xEDB88320u;
		else
			crc >>= 1;
		++bit;
	}
	return (crc);
}

uint32_t	ft_crc32(const void *data, size_t len)
{
	const unsigned char	*bytes;
	uint32_t				crc;
	size_t					i;

	bytes = (const unsigned char *)data;
	crc = 0xFFFFFFFFu;
	i = 0;
	while (i < len)
	{
		crc = (crc >> 8) ^ crc32_process_byte((crc ^ bytes[i]) & 0xFF);
		++i;
	}
	return (crc ^ 0xFFFFFFFFu);
}
