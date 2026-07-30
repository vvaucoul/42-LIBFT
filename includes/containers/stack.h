/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "vector.h"

/*
** Like C++'s std::stack: a LIFO adaptor. std::stack itself defaults to
** wrapping std::deque (any container with back()/push_back()/pop_back()
** would do) - here it wraps our Vector for exactly the same reason.
*/
typedef struct s_stack
{
    Vector  *vec;
}   t_stack;

#define Stack t_stack

Stack   *stack_new(void);
void    stack_delete(Stack *stack);
void    stack_push(Stack *stack, void *ptr);
void    stack_pop(Stack *stack);
void    *stack_top(Stack *stack);
size_t  stack_size(Stack *stack);
bool    stack_empty(Stack *stack);

#endif
