/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:59:23 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:06:16 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

// Function to start the timer
void startTimer(clock_t *start) {
    *start = clock();
}

// Function to stop the timer and calculate the elapsed time
double stopTimer(clock_t start) {
    clock_t end = clock();
    double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;
    return elapsedTime;
}
