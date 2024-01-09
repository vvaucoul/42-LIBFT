/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypto.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:52:15 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:53:56 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdlib.h>

// Function to encrypt a message
void encrypt(const char *message, size_t message_len, char *output, const char *key);

// Function to decrypt a message
void decrypt(const char *encrypted_message, size_t message_len, char *output, const char *key);

// Function to generate a hash from a message
void hash(const char *message, size_t message_len, char *output);

// Function to generate a secure random number
int secure_random(void);

// Function to generate a secure random string
void secure_random_string(char *output, size_t len);

// Function to generate a key pair for public key cryptography
void generate_key_pair(char *public_key, char *private_key);

// Function to encrypt a message with a public key
void public_key_encrypt(const char *message, size_t message_len, char *output, const char *public_key);

// Function to decrypt a message with a private key
void private_key_decrypt(const char *encrypted_message, size_t message_len, char *output, const char *private_key);

#endif /* !CRYPTO_H */