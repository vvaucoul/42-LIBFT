/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rsa_generate_keypair.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>
#include <stdio.h>

/* Primes chosen so any two distinct entries multiply to a value between
** 255 and 65536, keeping ciphertext bytes within 4 hex digits (ft_rsa_encrypt.c). */
static const uint32_t	g_rsa_primes[] = {
	17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79,
	83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
	157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
	229, 233, 239, 241, 251
};

#define RSA_PRIME_COUNT (sizeof(g_rsa_primes) / sizeof(g_rsa_primes[0]))

static uint32_t	rsa_random_prime_index(void)
{
	unsigned int	raw;

	raw = (unsigned int)ft_secure_random();
	return (raw % RSA_PRIME_COUNT);
}

static int64_t	rsa_extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y)
{
	int64_t	x1;
	int64_t	y1;
	int64_t	gcd;

	if (b == 0)
	{
		*x = 1;
		*y = 0;
		return (a);
	}
	gcd = rsa_extended_gcd(b, a % b, &x1, &y1);
	*x = y1;
	*y = x1 - (a / b) * y1;
	return (gcd);
}

/* Modular multiplicative inverse of `e` mod `phi`, normalized to [1, phi - 1];
** requires gcd(e, phi) == 1 to exist. */
static uint32_t	rsa_mod_inverse(uint32_t e, uint32_t phi)
{
	int64_t	x;
	int64_t	y;
	int64_t	result;

	rsa_extended_gcd((int64_t)e, (int64_t)phi, &x, &y);
	result = x % (int64_t)phi;
	if (result < 0)
		result += phi;
	return ((uint32_t)result);
}

static uint32_t	rsa_gcd(uint32_t a, uint32_t b)
{
	uint32_t	tmp;

	while (b != 0)
	{
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return (a);
}

/* Tries a short list of classic small public exponents and returns the
** first one coprime with phi (an inverse mod phi is required to exist). */
static uint32_t	rsa_pick_public_exponent(uint32_t phi)
{
	static const uint32_t	candidates[] = {17, 5, 7, 11, 13, 3, 19, 23, 29};
	size_t					i;

	i = 0;
	while (i < sizeof(candidates) / sizeof(candidates[0]))
	{
		if (candidates[i] < phi && rsa_gcd(candidates[i], phi) == 1)
			return (candidates[i]);
		++i;
	}
	return (3);
}

void	ft_rsa_generate_keypair(char *public_key, char *private_key)
{
	uint32_t	idx_p;
	uint32_t	idx_q;
	uint32_t	p;
	uint32_t	q;
	uint32_t	n;
	uint32_t	phi;
	uint32_t	e;
	uint32_t	d;

	if (!public_key || !private_key)
		return ;
	idx_p = rsa_random_prime_index();
	idx_q = rsa_random_prime_index();
	if (idx_q == idx_p)
		idx_q = (idx_q + 1) % RSA_PRIME_COUNT;
	p = g_rsa_primes[idx_p];
	q = g_rsa_primes[idx_q];
	n = p * q;
	phi = (p - 1) * (q - 1);
	e = rsa_pick_public_exponent(phi);
	d = rsa_mod_inverse(e, phi);
	snprintf(public_key, 32, "%u:%u", e, n);
	snprintf(private_key, 32, "%u:%u", d, n);
}
