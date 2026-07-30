/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor_encrypt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>
#include <libft.h>

/* Repeating-key XOR stream cipher; NULL/empty key copies the message
** through unchanged. */
void	ft_xor_encrypt(const char *message, size_t message_len,
			char *output, const char *key)
{
	size_t	key_len;
	size_t	i;

	if (!message || !output)
		return ;
	key_len = 0;
	if (key)
		key_len = ft_strlen(key);
	i = 0;
	while (i < message_len)
	{
		if (key_len == 0)
			output[i] = message[i];
		else
			output[i] = message[i] ^ key[i % key_len];
		++i;
	}
}
