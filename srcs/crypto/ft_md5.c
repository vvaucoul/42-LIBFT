/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>
#include <libft.h>

/* Real MD5 (RFC 1321): message-schedule per-round rotate amounts and the
** 64 sine-derived additive constants, both standard and fixed by the spec. */
static const uint32_t	g_md5_shifts[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t	g_md5_constants[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

typedef struct s_md5_ctx
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}	t_md5_ctx;

static uint32_t	md5_left_rotate(uint32_t x, uint32_t count)
{
	return ((x << count) | (x >> (32 - count)));
}

static void	md5_process_chunk(t_md5_ctx *ctx, const unsigned char *chunk)
{
	uint32_t	m[16];
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	f;
	uint32_t	g;
	uint32_t	i;

	i = 0;
	while (i < 16)
	{
		m[i] = (uint32_t)chunk[i * 4] | ((uint32_t)chunk[i * 4 + 1] << 8)
			| ((uint32_t)chunk[i * 4 + 2] << 16)
			| ((uint32_t)chunk[i * 4 + 3] << 24);
		++i;
	}
	a = ctx->a;
	b = ctx->b;
	c = ctx->c;
	d = ctx->d;
	i = 0;
	while (i < 64)
	{
		if (i < 16)
		{
			f = (b & c) | (~b & d);
			g = i;
		}
		else if (i < 32)
		{
			f = (d & b) | (~d & c);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			f = b ^ c ^ d;
			g = (3 * i + 5) % 16;
		}
		else
		{
			f = c ^ (b | ~d);
			g = (7 * i) % 16;
		}
		f = f + a + g_md5_constants[i] + m[g];
		a = d;
		d = c;
		c = b;
		b = b + md5_left_rotate(f, g_md5_shifts[i]);
		++i;
	}
	ctx->a += a;
	ctx->b += b;
	ctx->c += c;
	ctx->d += d;
}

/* Standard MD5 padding: a single 1-bit, zero bits up to 56 mod 64, then the
** original length in bits as a little-endian 64-bit integer. */
static unsigned char	*md5_pad_message(const void *data, size_t len,
	size_t *padded_len)
{
	size_t			zero_count;
	unsigned char	*buf;
	uint64_t		bit_len;
	size_t			i;

	zero_count = (55 - len % 64 + 64) % 64;
	*padded_len = len + 1 + zero_count + 8;
	buf = malloc(*padded_len);
	if (!buf)
		return (NULL);
	ft_memcpy(buf, data, len);
	buf[len] = 0x80;
	ft_memset(buf + len + 1, 0, zero_count);
	bit_len = (uint64_t)len * 8;
	i = 0;
	while (i < 8)
	{
		buf[len + 1 + zero_count + i] = (unsigned char)(bit_len >> (8 * i));
		++i;
	}
	return (buf);
}

static void	md5_write_digest(const t_md5_ctx *ctx, unsigned char digest[16])
{
	uint32_t	words[4];
	size_t		word;
	size_t		byte;

	words[0] = ctx->a;
	words[1] = ctx->b;
	words[2] = ctx->c;
	words[3] = ctx->d;
	word = 0;
	while (word < 4)
	{
		byte = 0;
		while (byte < 4)
		{
			digest[word * 4 + byte] = (unsigned char)(words[word]
					>> (8 * byte));
			++byte;
		}
		++word;
	}
}

void	ft_md5(const void *data, size_t len, unsigned char digest[16])
{
	t_md5_ctx		ctx;
	unsigned char	*padded;
	size_t			padded_len;
	size_t			offset;

	if (!digest || (!data && len != 0))
		return ;
	ctx.a = 0x67452301;
	ctx.b = 0xefcdab89;
	ctx.c = 0x98badcfe;
	ctx.d = 0x10325476;
	padded = md5_pad_message(data, len, &padded_len);
	if (!padded)
		return ;
	offset = 0;
	while (offset < padded_len)
	{
		md5_process_chunk(&ctx, padded + offset);
		offset += 64;
	}
	free(padded);
	md5_write_digest(&ctx, digest);
}

char	*ft_md5_str(const void *data, size_t len)
{
	static const char	hex_digits[] = "0123456789abcdef";
	unsigned char		digest[16];
	char				*str;
	size_t				i;

	if (!(str = malloc(33)))
		return (NULL);
	ft_md5(data, len, digest);
	i = 0;
	while (i < 16)
	{
		str[i * 2] = hex_digits[digest[i] >> 4];
		str[i * 2 + 1] = hex_digits[digest[i] & 0xF];
		++i;
	}
	str[32] = '\0';
	return (str);
}
