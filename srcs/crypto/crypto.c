/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypto.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:52:08 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:53:35 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>
#include <libft.h>

void encrypt(const char *message, size_t message_len, char *output, const char *key) {
    (void)message;
    (void)message_len;
    (void)output;
    (void)key;
}

void decrypt(const char *encrypted_message, size_t message_len, char *output, const char *key) {
    (void)encrypted_message;
    (void)message_len;
    (void)output;
    (void)key;
}

void hash(const char *message, size_t message_len, char *output) {
    (void)message;
    (void)message_len;
    (void)output;
}

int secure_random(void) {
    return 0;
}

void secure_random_string(char *output, size_t len) {
    (void)output;
    (void)len;
}

void generate_key_pair(char *public_key, char *private_key) {
    (void)public_key;
    (void)private_key;
}

void public_key_encrypt(const char *message, size_t message_len, char *output, const char *public_key) {
    (void)message;
    (void)message_len;
    (void)output;
    (void)public_key;
}

void private_key_decrypt(const char *encrypted_message, size_t message_len, char *output, const char *private_key) {
    (void)encrypted_message;
    (void)message_len;
    (void)output;
    (void)private_key;
}