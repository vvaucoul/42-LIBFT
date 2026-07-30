/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypto.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdlib.h>
#include <stdint.h>

/*
** Disclaimers below are load-bearing, not boilerplate - read them before
** reusing this module outside of this school project:
**
**  - ft_xor_encrypt/decrypt: a classic XOR stream cipher. Secure ONLY if the
**    key is truly random and at least as long as the message (one-time pad).
**    With a short reused key (the common case here) it is trivially broken
**    by frequency analysis. Educational value only.
**  - ft_hash_djb2/ft_hash_fnv1a32/ft_crc32: fast NON-cryptographic hashes
**    (hash tables, checksums). Do not use them where collision-resistance
**    against an attacker matters.
**  - ft_md5: the real MD5 algorithm (RFC 1321), bit-for-bit compatible with
**    `md5sum`. MD5 is cryptographically broken (collisions are practical) -
**    fine for checksums/dedup, never for signatures or password hashing.
**  - ft_secure_random/ft_secure_random_string: read from the kernel CSPRNG
**    (/dev/urandom), suitable for real secret-generation use, with a
**    documented non-random fallback path if /dev/urandom cannot be opened.
**  - ft_rsa_*: a real, textbook RSA implementation (key generation via
**    modular inverse, encryption/decryption via modular exponentiation),
**    but with a deliberately tiny (16-bit) modulus so it can print keys as
**    short decimal strings and encode one byte per 4 hex digits. This makes
**    it trivially breakable by brute force / factoring - it demonstrates
**    HOW public-key crypto works, it is not a usable cipher.
*/

/* --------------------------------------------------------------- CIPHERS */

void	ft_xor_encrypt(const char *message, size_t message_len,
			char *output, const char *key);
void	ft_xor_decrypt(const char *encrypted_message, size_t message_len,
			char *output, const char *key);

/* ---------------------------------------------------------------- HASHES */

uint32_t	ft_hash_djb2(const void *data, size_t len);
uint32_t	ft_hash_fnv1a32(const void *data, size_t len);
uint32_t	ft_crc32(const void *data, size_t len);

void	ft_md5(const void *data, size_t len, unsigned char digest[16]);
char	*ft_md5_str(const void *data, size_t len);

/* --------------------------------------------------------------- BASE 64 */

char	*ft_base64_encode(const void *data, size_t len);
void	*ft_base64_decode(const char *b64, size_t *out_len);

/* --------------------------------------------------------- SECURE RANDOM */

int		ft_secure_random(void);
void	ft_secure_random_string(char *output, size_t len);

/* -------------------------------------------------------- TOY RSA (16-bit) */

/*
** public_key/private_key are written as "e:n" / "d:n" decimal strings;
** callers must provide buffers of at least 32 bytes.
*/
void	ft_rsa_generate_keypair(char *public_key, char *private_key);

/*
** output must hold (message_len * 4 + 1) bytes: each input byte becomes
** exactly 4 hex digits.
*/
void	ft_rsa_encrypt(const char *message, size_t message_len,
			char *output, const char *public_key);

/*
** encrypted_len is the length of `encrypted_message` in hex characters
** (a multiple of 4); output must hold at least (encrypted_len / 4 + 1)
** bytes.
*/
void	ft_rsa_decrypt(const char *encrypted_message, size_t encrypted_len,
			char *output, const char *private_key);

#endif /* !CRYPTO_H */
