/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "framework/test_framework.h"

int	main(int argc, char **argv)
{
	int	verbose;

	verbose = (argc > 1 && (!strcmp(argv[1], "-v")
			|| !strcmp(argv[1], "--verbose")));
	printf("\033[1mlibft test suite\033[0m\n");
	return (test_run_all(verbose));
}
