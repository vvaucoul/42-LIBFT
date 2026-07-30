/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "libft.h"

/*
** Like C++'s std::queue: a FIFO adaptor (std::queue defaults to
** std::deque). Built directly on doubly-linked t_dlist nodes, keeping our
** own front/back pointers so push/pop are true O(1) - NOT by calling
** ft_dlstadd_back(), which walks the whole list to find the tail every
** time (O(n) per call) since it has no cached tail pointer to work with.
*/
typedef struct s_queue
{
    t_dlist *front;
    t_dlist *back;
    size_t  size;
}   t_queue;

#define Queue t_queue

Queue   *queue_new(void);
void    queue_delete(Queue *queue, bool free_data);
void    queue_push(Queue *queue, void *data);
void    *queue_pop(Queue *queue);
void    *queue_front(Queue *queue);
void    *queue_back(Queue *queue);
size_t  queue_size(Queue *queue);
bool    queue_empty(Queue *queue);

#endif
