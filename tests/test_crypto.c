/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_crypto.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <crypto.h>
#include "framework/test_framework.h"

/* --------------------------------------------------------------- CIPHERS */

TEST(crypto, xor_encrypt_decrypt_round_trip)
{
	const char	*msg = "secret message";
	size_t		len = ft_strlen(msg);
	char		enc[32];
	char		dec[32];

	ft_xor_encrypt(msg, len, enc, "key");
	ASSERT(memcmp(enc, msg, len) != 0);
	ft_xor_decrypt(enc, len, dec, "key");
	dec[len] = '\0';
	ASSERT_EQ_STR(dec, msg);
}

TEST(crypto, xor_wrong_key_does_not_round_trip)
{
	const char	*msg = "secret message";
	size_t		len = ft_strlen(msg);
	char		enc[32];
	char		dec[32];

	ft_xor_encrypt(msg, len, enc, "key");
	ft_xor_decrypt(enc, len, dec, "not-the-key");
	dec[len] = '\0';
	ASSERT(memcmp(dec, msg, len) != 0);
}

TEST(crypto, xor_empty_key_is_passthrough)
{
	const char	*msg = "unchanged";
	size_t		len = ft_strlen(msg);
	char		out[32];

	ft_xor_encrypt(msg, len, out, "");
	out[len] = '\0';
	ASSERT_EQ_STR(out, msg);
	ft_xor_encrypt(msg, len, out, NULL);
	out[len] = '\0';
	ASSERT_EQ_STR(out, msg);
}

/* ---------------------------------------------------------------- HASHES */

TEST(crypto, hash_djb2_known_values)
{
	ASSERT_EQ_UINT(ft_hash_djb2("", 0), 0x1505u);
	ASSERT_EQ_UINT(ft_hash_djb2("hello", 5), 0xf923099u);
	ASSERT_EQ_UINT(ft_hash_djb2("The quick brown fox", 19), 0x97c3fcf8u);
}

TEST(crypto, hash_fnv1a32_known_values)
{
	ASSERT_EQ_UINT(ft_hash_fnv1a32("", 0), 0x811c9dc5u);
	ASSERT_EQ_UINT(ft_hash_fnv1a32("hello", 5), 0x4f9f2cabu);
	ASSERT_EQ_UINT(ft_hash_fnv1a32("The quick brown fox", 19), 0xae4d67e2u);
}

TEST(crypto, crc32_known_check_value)
{
	/* The canonical CRC-32 (IEEE 802.3) self-check value. */
	ASSERT_EQ_UINT(ft_crc32("123456789", 9), 0xcbf43926u);
	ASSERT_EQ_UINT(ft_crc32("", 0), 0u);
}

TEST(crypto, crc32_matches_reference_strings)
{
	ASSERT_EQ_UINT(ft_crc32("hello", 5), 0x3610a686u);
	ASSERT_EQ_UINT(ft_crc32("The quick brown fox", 19), 0xb74574deu);
}

TEST(crypto, md5_matches_known_digests)
{
	char	*s;

	s = ft_md5_str("", 0);
	ASSERT_EQ_STR(s, "d41d8cd98f00b204e9800998ecf8427e");
	free(s);

	s = ft_md5_str("hello", 5);
	ASSERT_EQ_STR(s, "5d41402abc4b2a76b9719d911017c592");
	free(s);

	s = ft_md5_str("The quick brown fox", 19);
	ASSERT_EQ_STR(s, "a2004f37730b9445670a738fa0fc9ee5");
	free(s);
}

TEST(crypto, md5_handles_multi_block_input)
{
	char	buf[200];
	char	*s;

	memset(buf, 'a', sizeof(buf));
	s = ft_md5_str(buf, sizeof(buf));
	ASSERT_NOT_NULL(s);
	ASSERT_EQ_INT((int)ft_strlen(s), 32);
	free(s);
}

TEST(crypto, md5_binary_digest_matches_hex_string)
{
	unsigned char	digest[16];
	char			*hex;
	char			rebuilt[33];
	static const char	table[] = "0123456789abcdef";
	int				i;

	ft_md5("hello", 5, digest);
	hex = ft_md5_str("hello", 5);
	i = 0;
	while (i < 16)
	{
		rebuilt[i * 2] = table[digest[i] >> 4];
		rebuilt[i * 2 + 1] = table[digest[i] & 0xF];
		++i;
	}
	rebuilt[32] = '\0';
	ASSERT_EQ_STR(rebuilt, hex);
	free(hex);
}

/* --------------------------------------------------------------- BASE 64 */

TEST(crypto, base64_encode_known_vectors)
{
	char	*s;

	s = ft_base64_encode("Man", 3);
	ASSERT_EQ_STR(s, "TWFu");
	free(s);

	s = ft_base64_encode("hello world", 11);
	ASSERT_EQ_STR(s, "aGVsbG8gd29ybGQ=");
	free(s);

	s = ft_base64_encode("f", 1);
	ASSERT_EQ_STR(s, "Zg==");
	free(s);

	s = ft_base64_encode("fo", 2);
	ASSERT_EQ_STR(s, "Zm8=");
	free(s);

	s = ft_base64_encode("foo", 3);
	ASSERT_EQ_STR(s, "Zm9v");
	free(s);

	s = ft_base64_encode("", 0);
	ASSERT_EQ_STR(s, "");
	free(s);
}

TEST(crypto, base64_decode_known_vectors)
{
	void	*out;
	size_t	out_len;

	out = ft_base64_decode("TWFu", &out_len);
	ASSERT_EQ_UINT(out_len, 3u);
	ASSERT_EQ_MEM(out, "Man", 3);
	free(out);

	out = ft_base64_decode("aGVsbG8gd29ybGQ=", &out_len);
	ASSERT_EQ_UINT(out_len, 11u);
	ASSERT_EQ_MEM(out, "hello world", 11);
	free(out);

	out = ft_base64_decode("Zg==", &out_len);
	ASSERT_EQ_UINT(out_len, 1u);
	ASSERT_EQ_MEM(out, "f", 1);
	free(out);
}

TEST(crypto, base64_decode_rejects_malformed_input)
{
	size_t	out_len;

	ASSERT_NULL(ft_base64_decode("abc", &out_len));
	ASSERT_NULL(ft_base64_decode("abc!", &out_len));
	ASSERT_NULL(ft_base64_decode(NULL, &out_len));
}

TEST(crypto, base64_round_trip_all_byte_values)
{
	unsigned char	data[256];
	int				i;
	char			*encoded;
	void			*decoded;
	size_t			decoded_len;

	i = 0;
	while (i < 256)
	{
		data[i] = (unsigned char)i;
		++i;
	}
	encoded = ft_base64_encode(data, sizeof(data));
	decoded = ft_base64_decode(encoded, &decoded_len);
	ASSERT_EQ_UINT(decoded_len, sizeof(data));
	ASSERT_EQ_MEM(decoded, data, sizeof(data));
	free(encoded);
	free(decoded);
}

/* --------------------------------------------------------- SECURE RANDOM */

/* Statistical, not exact: with a real CSPRNG, 20 colliding draws is astronomically unlikely. */
TEST(crypto, secure_random_is_not_constant)
{
	int	values[20];
	int	all_same;
	int	i;

	i = 0;
	while (i < 20)
	{
		values[i] = ft_secure_random();
		++i;
	}
	all_same = 1;
	i = 1;
	while (i < 20)
	{
		if (values[i] != values[0])
			all_same = 0;
		++i;
	}
	ASSERT_MSG(!all_same,
		"ft_secure_random() returned the same value 20 times in a row");
}

TEST(crypto, secure_random_string_fills_buffer_and_terminates)
{
	char	output[17];

	memset(output, 'Z', sizeof(output));
	ft_secure_random_string(output, sizeof(output));
	ASSERT_EQ_INT((int)ft_strlen(output), 16);
	ASSERT_EQ_INT(output[16], '\0');
}

TEST(crypto, secure_random_string_only_uses_charset)
{
	char	output[65];
	int		i;
	int		c;
	int		valid;

	ft_secure_random_string(output, sizeof(output));
	i = 0;
	while (i < 64)
	{
		c = (unsigned char)output[i];
		valid = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
			|| (c >= '0' && c <= '9');
		ASSERT_MSG(valid, "secure_random_string produced a non-alnum byte");
		++i;
	}
}

TEST(crypto, secure_random_string_zero_and_one_len_are_safe)
{
	char	output[4];

	output[0] = 'X';
	ft_secure_random_string(output, 0);
	ASSERT_EQ_INT(output[0], 'X');
	ft_secure_random_string(output, 1);
	ASSERT_EQ_INT(output[0], '\0');
}

/* -------------------------------------------------------- TOY RSA (16-bit) */

TEST(crypto, rsa_encrypt_decrypt_round_trip)
{
	char	pub[32];
	char	priv[32];
	char	cipher[64];
	char	plain[16];
	const char	*msg = "Hi!";

	ft_rsa_generate_keypair(pub, priv);
	ft_rsa_encrypt(msg, ft_strlen(msg), cipher, pub);
	ft_rsa_decrypt(cipher, ft_strlen(cipher), plain, priv);
	ASSERT_EQ_STR(plain, msg);
}

TEST(crypto, rsa_round_trip_covers_every_byte_value)
{
	char			pub[32];
	char			priv[32];
	unsigned char	message[256];
	char			cipher[256 * 4 + 1];
	unsigned char	plain[257];
	int				i;

	ft_rsa_generate_keypair(pub, priv);
	i = 0;
	while (i < 256)
	{
		message[i] = (unsigned char)i;
		++i;
	}
	ft_rsa_encrypt((const char *)message, sizeof(message), cipher, pub);
	ft_rsa_decrypt(cipher, ft_strlen(cipher), (char *)plain, priv);
	ASSERT_EQ_MEM(plain, message, sizeof(message));
}

TEST(crypto, rsa_generate_keypair_varies_across_calls)
{
	char	pub_a[32];
	char	priv_a[32];
	char	pub_b[32];
	char	priv_b[32];
	int		i;
	int		any_diff;

	any_diff = 0;
	ft_rsa_generate_keypair(pub_a, priv_a);
	i = 0;
	while (i < 20 && !any_diff)
	{
		ft_rsa_generate_keypair(pub_b, priv_b);
		if (strcmp(pub_a, pub_b) != 0)
			any_diff = 1;
		++i;
	}
	ASSERT_MSG(any_diff,
		"ft_rsa_generate_keypair() produced the same key 20 times in a row");
}

TEST(crypto, rsa_wrong_private_key_does_not_decrypt_correctly)
{
	char		pub_a[32];
	char		priv_a[32];
	char		pub_b[32];
	char		priv_b[32];
	char		cipher[64];
	char		plain[16];
	const char	*msg = "Hi!";
	int			tries;

	ft_rsa_generate_keypair(pub_a, priv_a);
	tries = 0;
	do {
		ft_rsa_generate_keypair(pub_b, priv_b);
		++tries;
	} while (strcmp(priv_a, priv_b) == 0 && tries < 20);
	ft_rsa_encrypt(msg, ft_strlen(msg), cipher, pub_a);
	ft_rsa_decrypt(cipher, ft_strlen(cipher), plain, priv_b);
	ASSERT(memcmp(plain, msg, ft_strlen(msg)) != 0);
}
