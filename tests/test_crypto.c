/* ************************************************************************** */
/*   test_crypto.c - srcs/crypto/crypto.c                                    */
/*                                                                            */
/*   Every function in this file is an unimplemented stub: parameters are   */
/*   cast to (void), no output buffer is ever written to, and there is no   */
/*   algorithm of any kind (not XOR, not a real hash, nothing). These tests */
/*   document exactly that - they are not "known quirks", the module needs */
/*   a real implementation before it can do anything a caller would expect. */
/* ************************************************************************** */

#include <libft.h>
#include <crypto.h>
#include "framework/test_framework.h"

TEST(crypto, encrypt_does_not_transform_output_known_unimplemented)
{
	char output[16];

	memset(output, 'Z', sizeof(output));
	encrypt("secret message", 14, output, "key");
	ASSERT_MSG(!(output[0] == 'Z' && output[1] == 'Z'),
		"encrypt() should write ciphertext into `output`, but it is an "
		"unimplemented stub that never touches the buffer at all");
}

TEST(crypto, decrypt_does_not_transform_output_known_unimplemented)
{
	char output[16];

	memset(output, 'Z', sizeof(output));
	decrypt("ciphertext", 10, output, "key");
	ASSERT_MSG(!(output[0] == 'Z' && output[1] == 'Z'),
		"decrypt() should write plaintext into `output`, but it is an "
		"unimplemented stub that never touches the buffer at all");
}

TEST(crypto, hash_does_not_write_output_known_unimplemented)
{
	char output[16];

	memset(output, 'Z', sizeof(output));
	hash("some message", 12, output);
	ASSERT_MSG(!(output[0] == 'Z' && output[1] == 'Z'),
		"hash() should write a digest into `output`, but it is an "
		"unimplemented stub that never touches the buffer at all");
}

/* secure_random() is `return (0);` - a hardcoded constant. No srand()
** call exists anywhere in this file either. */
TEST(crypto, secure_random_is_not_random_known_unimplemented)
{
	int values[5];

	for (int i = 0; i < 5; ++i)
		values[i] = secure_random();
	for (int i = 0; i < 5; ++i)
		ASSERT_EQ_INT(values[i], 0);
}

TEST(crypto, secure_random_string_does_not_write_output_known_unimplemented)
{
	char output[16];

	memset(output, 'Z', sizeof(output));
	secure_random_string(output, sizeof(output));
	ASSERT_MSG(!(output[0] == 'Z' && output[1] == 'Z'),
		"secure_random_string() should fill `output`, but it is an "
		"unimplemented stub that never touches the buffer at all");
}

TEST(crypto, generate_key_pair_does_not_write_output_known_unimplemented)
{
	char pub[16];
	char priv[16];

	memset(pub, 'Z', sizeof(pub));
	memset(priv, 'Z', sizeof(priv));
	generate_key_pair(pub, priv);
	ASSERT_MSG(!(pub[0] == 'Z' && priv[0] == 'Z'),
		"generate_key_pair() should fill both key buffers, but it is an "
		"unimplemented stub that never touches either of them");
}
