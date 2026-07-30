/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64_encode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>

static const char	g_base64_table[64] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void	base64_encode_triplet(unsigned char b0, unsigned char b1,
	unsigned char b2, char out[4])
{
	out[0] = g_base64_table[b0 >> 2];
	out[1] = g_base64_table[((b0 & 0x03) << 4) | (b1 >> 4)];
	out[2] = g_base64_table[((b1 & 0x0F) << 2) | (b2 >> 6)];
	out[3] = g_base64_table[b2 & 0x3F];
}

char	*ft_base64_encode(const void *data, size_t len)
{
	const unsigned char	*bytes;
	char					*out;
	size_t					out_len;
	size_t					i;
	size_t					o;
	unsigned char			b0;
	unsigned char			b1;
	unsigned char			b2;

	bytes = (const unsigned char *)data;
	if (!data && len != 0)
		return (NULL);
	out_len = ((len + 2) / 3) * 4;
	if (!(out = malloc(out_len + 1)))
		return (NULL);
	i = 0;
	o = 0;
	while (i < len)
	{
		b0 = bytes[i];
		b1 = 0;
		b2 = 0;
		if (i + 1 < len)
			b1 = bytes[i + 1];
		if (i + 2 < len)
			b2 = bytes[i + 2];
		base64_encode_triplet(b0, b1, b2, out + o);
		if (i + 1 >= len)
			out[o + 2] = '=';
		if (i + 2 >= len)
			out[o + 3] = '=';
		i += 3;
		o += 4;
	}
	out[out_len] = '\0';
	return (out);
}
