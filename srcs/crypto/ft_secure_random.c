/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure_random.c                                 :+:      :+:    :+:   */
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

/* Reads /dev/urandom; if unavailable, falls back to rand() seeded from
** time+pid (not cryptographically secure). */
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

int	ft_secure_random(void)
{
	unsigned char	bytes[sizeof(int)];
	unsigned int	value;
	size_t			i;

	secure_random_bytes(bytes, sizeof(bytes));
	value = 0;
	i = 0;
	while (i < sizeof(bytes))
	{
		value |= ((unsigned int)bytes[i]) << (8 * i);
		++i;
	}
	return ((int)value);
}
