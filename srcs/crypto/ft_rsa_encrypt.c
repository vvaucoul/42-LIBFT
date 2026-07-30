/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rsa_encrypt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>
#include <stdio.h>

/* Parses the "e:n" / "d:n" key format produced by
** ft_rsa_generate_keypair(). */
static void	rsa_parse_key(const char *key, uint64_t *first, uint64_t *second)
{
	unsigned long long	a;
	unsigned long long	b;

	a = 0;
	b = 0;
	if (key)
		sscanf(key, "%llu:%llu", &a, &b);
	*first = (uint64_t)a;
	*second = (uint64_t)b;
}

static uint64_t	rsa_modpow(uint64_t base, uint64_t exp, uint64_t mod)
{
	uint64_t	result;

	result = 1;
	base = base % mod;
	while (exp > 0)
	{
		if (exp & 1)
			result = (result * base) % mod;
		exp >>= 1;
		base = (base * base) % mod;
	}
	return (result);
}

static const char	g_hex_digits[] = "0123456789abcdef";

/* Textbook RSA: every plaintext byte is independently raised to `e` mod
** `n` and written as 4 hex digits (n < 65536, so the result always fits). */
void	ft_rsa_encrypt(const char *message, size_t message_len,
			char *output, const char *public_key)
{
	uint64_t	e;
	uint64_t	n;
	uint64_t	cipher;
	size_t		i;

	if (!message || !output || !public_key)
		return ;
	rsa_parse_key(public_key, &e, &n);
	if (n == 0)
		return ;
	i = 0;
	while (i < message_len)
	{
		cipher = rsa_modpow((unsigned char)message[i], e, n);
		output[i * 4] = g_hex_digits[(cipher >> 12) & 0xF];
		output[i * 4 + 1] = g_hex_digits[(cipher >> 8) & 0xF];
		output[i * 4 + 2] = g_hex_digits[(cipher >> 4) & 0xF];
		output[i * 4 + 3] = g_hex_digits[cipher & 0xF];
		++i;
	}
	output[message_len * 4] = '\0';
}
