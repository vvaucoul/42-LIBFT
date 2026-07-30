/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor_decrypt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>

/* XOR is its own inverse: decrypting a message is the exact same operation
** as encrypting it, given the same key. */
void	ft_xor_decrypt(const char *encrypted_message, size_t message_len,
			char *output, const char *key)
{
	ft_xor_encrypt(encrypted_message, message_len, output, key);
}
