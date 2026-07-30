/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64_decode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>

static int	base64_char_value(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 26);
	if (c >= '0' && c <= '9')
		return (c - '0' + 52);
	if (c == '+')
		return (62);
	if (c == '/')
		return (63);
	return (-1);
}

static size_t	base64_input_len(const char *b64)
{
	size_t	len;

	len = 0;
	while (b64[len])
		++len;
	return (len);
}

/* Returns NULL for malformed input (length not a multiple of 4, or a
** non-alphabet / non-padding character before the end). On success,
** *out_len receives the decoded byte count. */
void	*ft_base64_decode(const char *b64, size_t *out_len)
{
	size_t			in_len;
	size_t			pad;
	unsigned char	*out;
	size_t			i;
	size_t			o;
	int				v0;
	int				v1;
	int				v2;
	int				v3;

	if (!b64 || !out_len)
		return (NULL);
	in_len = base64_input_len(b64);
	if (in_len == 0 || in_len % 4 != 0)
		return (NULL);
	pad = 0;
	if (in_len >= 1 && b64[in_len - 1] == '=')
		++pad;
	if (in_len >= 2 && b64[in_len - 2] == '=')
		++pad;
	if (!(out = malloc((in_len / 4) * 3 + 1)))
		return (NULL);
	i = 0;
	o = 0;
	while (i < in_len)
	{
		v0 = base64_char_value(b64[i]);
		v1 = base64_char_value(b64[i + 1]);
		v2 = base64_char_value(b64[i + 2]);
		v3 = base64_char_value(b64[i + 3]);
		if (v0 < 0 || v1 < 0 || (b64[i + 2] != '=' && v2 < 0)
			|| (b64[i + 3] != '=' && v3 < 0))
		{
			free(out);
			return (NULL);
		}
		out[o] = (unsigned char)((v0 << 2) | (v1 >> 4));
		if (b64[i + 2] != '=')
			out[o + 1] = (unsigned char)(((v1 & 0x0F) << 4) | (v2 >> 2));
		if (b64[i + 3] != '=')
			out[o + 2] = (unsigned char)(((v2 & 0x03) << 6) | v3);
		i += 4;
		o += 3;
	}
	*out_len = o - pad;
	out[*out_len] = '\0';
	return (out);
}
