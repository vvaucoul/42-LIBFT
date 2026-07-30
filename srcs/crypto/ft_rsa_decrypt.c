/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rsa_decrypt.c                                   :+:      :+:    :+:   */
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

static int	rsa_hex_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

/* Reverses ft_rsa_encrypt(): every group of 4 hex digits is parsed back
** into a ciphertext value and raised to `d` mod `n` to recover the byte. */
void	ft_rsa_decrypt(const char *encrypted_message, size_t encrypted_len,
			char *output, const char *private_key)
{
	uint64_t	d;
	uint64_t	n;
	uint64_t	cipher;
	size_t		i;
	size_t		byte_count;

	if (!encrypted_message || !output || !private_key)
		return ;
	rsa_parse_key(private_key, &d, &n);
	if (n == 0)
		return ;
	byte_count = encrypted_len / 4;
	i = 0;
	while (i < byte_count)
	{
		cipher = ((uint64_t)rsa_hex_value(encrypted_message[i * 4]) << 12)
			| ((uint64_t)rsa_hex_value(encrypted_message[i * 4 + 1]) << 8)
			| ((uint64_t)rsa_hex_value(encrypted_message[i * 4 + 2]) << 4)
			| (uint64_t)rsa_hex_value(encrypted_message[i * 4 + 3]);
		output[i] = (char)rsa_modpow(cipher, d, n);
		++i;
	}
	output[byte_count] = '\0';
}
