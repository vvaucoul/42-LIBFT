/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

Queue *queue_new(void)
{
    Queue *queue;

    if (!(queue = malloc(sizeof(Queue))))
        return (NULL);
    queue->front = NULL;
    queue->back = NULL;
    queue->size = 0;
    return (queue);
}

void queue_delete(Queue *queue, bool free_data)
{
    t_dlist *cur;
    t_dlist *next;

    if (!queue)
        return ;
    cur = queue->front;
    while (cur)
    {
        next = cur->next;
        if (free_data)
            free(cur->data);
        free(cur);
        cur = next;
    }
    free(queue);
}

void queue_push(Queue *queue, void *data)
{
    t_dlist *node;

    if (!queue || !(node = ft_dlstnew(data)))
        return ;
    if (!queue->back)
    {
        queue->front = node;
        queue->back = node;
    }
    else
    {
        node->prev = queue->back;
        queue->back->next = node;
        queue->back = node;
    }
    ++queue->size;
}

void *queue_pop(Queue *queue)
{
    t_dlist *node;
    void *data;

    if (!queue || !queue->front)
        return (NULL);
    node = queue->front;
    data = node->data;
    queue->front = node->next;
    if (queue->front)
        queue->front->prev = NULL;
    else
        queue->back = NULL;
    free(node);
    --queue->size;
    return (data);
}

void *queue_front(Queue *queue)
{
    if (!queue || !queue->front)
        return (NULL);
    return (queue->front->data);
}

void *queue_back(Queue *queue)
{
    if (!queue || !queue->back)
        return (NULL);
    return (queue->back->data);
}

size_t queue_size(Queue *queue)
{
    if (!queue)
        return (0);
    return (queue->size);
}

bool queue_empty(Queue *queue)
{
    return (!queue || queue->size == 0);
}
