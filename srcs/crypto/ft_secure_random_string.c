/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure_random_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <crypto.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

static const char	g_charset[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

/* See ft_secure_random.c for the identical rationale behind this fallback. */
static void	secure_random_bytes(unsigned char *buf, size_t len)
{
	int		fd;
	ssize_t	got;
	size_t	i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd >= 0)
	{
		got = read(fd, buf, len);
		close(fd);
		if (got == (ssize_t)len)
			return ;
	}
	srand((unsigned int)time(NULL) ^ (unsigned int)getpid());
	i = 0;
	while (i < len)
	{
		buf[i] = (unsigned char)(rand() % 256);
		++i;
	}
}

/* Fills `output` with (len - 1) random chars + a null terminator, so `len`
** is the buffer size like snprintf; len == 0 writes nothing. */
void	ft_secure_random_string(char *output, size_t len)
{
	unsigned char	*bytes;
	size_t			i;

	if (!output || len == 0)
		return ;
	if (len == 1)
	{
		output[0] = '\0';
		return ;
	}
	if (!(bytes = malloc(len - 1)))
		return ;
	secure_random_bytes(bytes, len - 1);
	i = 0;
	while (i < len - 1)
	{
		output[i] = g_charset[bytes[i] % (sizeof(g_charset) - 1)];
		++i;
	}
	output[len - 1] = '\0';
	free(bytes);
}
