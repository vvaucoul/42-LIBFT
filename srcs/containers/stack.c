/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

Stack *stack_new(void)
{
    Stack *stack;

    if (!(stack = malloc(sizeof(Stack))))
        return (NULL);
    if (!(stack->vec = vector_new(sizeof(void *), 0)))
    {
        free(stack);
        return (NULL);
    }
    return (stack);
}

void stack_delete(Stack *stack)
{
    if (!stack)
        return ;
    vector_delete(stack->vec);
    free(stack);
}

void stack_push(Stack *stack, void *ptr)
{
    if (!stack)
        return ;
    vector_push_back(stack->vec, ptr);
}

void stack_pop(Stack *stack)
{
    if (!stack)
        return ;
    vector_pop_back(stack->vec);
}

void *stack_top(Stack *stack)
{
    if (!stack)
        return (NULL);
    return (vector_back(stack->vec));
}

size_t stack_size(Stack *stack)
{
    if (!stack)
        return (0);
    return (vector_size(stack->vec));
}

bool stack_empty(Stack *stack)
{
    if (!stack)
        return (true);
    return (vector_empty(stack->vec));
}
