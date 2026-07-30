/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#define VECTOR_INITIAL_CAPACITY 4

/* Grows capacity by doubling so push_back/pop_back stay amortized O(1). */
static bool vector_ensure_capacity(Vector *vector, size_t needed)
{
    void **new_root;
    size_t new_capacity;
    size_t i;

    if (needed <= vector->capacity)
        return (true);
    new_capacity = vector->capacity ? vector->capacity * 2
        : VECTOR_INITIAL_CAPACITY;
    while (new_capacity < needed)
        new_capacity *= 2;
    if (!(new_root = malloc(sizeof(void *) * new_capacity)))
        return (false);
    i = 0;
    while (i < vector->size)
    {
        new_root[i] = vector->root[i];
        ++i;
    }
    free(vector->root);
    vector->root = new_root;
    vector->capacity = new_capacity;
    return (true);
}

static size_t vector_find(Vector *vector, void *ptr)
{
    size_t i;

    if (!vector)
        return (0);
    i = 0;
    while (i < vector->size)
    {
        if ((vector->root)[i] == ptr)
            return (i);
        i++;
    }
    return (i);
}

Vector *vector_new(size_t size, size_t count)
{
    Vector *vector;

    /* size is unused: element storage is always sizeof(void *) rows. */
    (void)size;
    if (!(vector = (Vector *)ft_calloc(sizeof(Vector), 1)))
        return (NULL);
    vector->root = NULL;
    vector->size = 0;
    vector->capacity = 0;
    if (count > 0 && !vector_ensure_capacity(vector, count))
    {
        free(vector);
        return (NULL);
    }
    return (vector);
}

void vector_delete(Vector *vector)
{
    if (!vector)
        return ;
    free(vector->root);
    free(vector);
}

/*******************************************************************************
 *                                  CAPACITY                                   *
 ******************************************************************************/

size_t vector_size(Vector *vector)
{
    if (!vector)
        return (0);
    return (vector->size);
}

size_t vector_max_size(Vector *vector)
{
    (void)vector;
    return ((size_t)-1 / sizeof(void *));
}

void vector_resize(Vector *vector, size_t size)
{
    size_t i;

    if (!vector)
        return ;
    if (size > vector->size && !vector_ensure_capacity(vector, size))
        return ;
    i = vector->size;
    while (i < size)
    {
        vector->root[i] = NULL;
        ++i;
    }
    vector->size = size;
}

size_t vector_capacity(Vector *vector)
{
    if (!vector)
        return (0);
    return (vector->capacity);
}

int vector_empty(Vector *vector)
{
    return (vector_size(vector) == 0);
}

void vector_reserve(Vector *vector, size_t size)
{
    if (!vector)
        return ;
    vector_ensure_capacity(vector, size);
}

/*******************************************************************************
 *                              ELEMENT - ACCESS                               *
 ******************************************************************************/

void *vector_at(Vector *vector, size_t index)
{
    if (!vector || index >= vector->size)
        return (NULL);
    return (vector->root[index]);
}

void *vector_front(Vector *vector)
{
    if (!vector || vector->size == 0)
        return (NULL);
    return (vector->root[0]);
}

void *vector_back(Vector *vector)
{
    if (!vector || vector->size == 0)
        return (NULL);
    return (vector->root[vector->size - 1]);
}

void *vector_data(Vector *vector)
{
    if (!vector)
        return (NULL);
    return ((void *)vector->root);
}

/*******************************************************************************
 *                                  MODIFIERS                                  *
 ******************************************************************************/

void vector_assign(Vector *vector, void **ptrs)
{
    size_t i;
    size_t ptrs_len;

    if (!vector || !ptrs || !ptrs[0])
        return ;
    ptrs_len = 0;
    while (ptrs[ptrs_len])
        ++ptrs_len;
    vector_resize(vector, ptrs_len);
    i = 0;
    while (i < vector->size)
    {
        vector->root[i] = ptrs[i];
        ++i;
    }
}

void vector_push_back(Vector *vector, void *ptr)
{
    if (!vector || !vector_ensure_capacity(vector, vector->size + 1))
        return ;
    vector->root[vector->size] = ptr;
    ++vector->size;
}

void vector_pop_back(Vector *vector)
{
    if (!vector || vector->size == 0)
        return ;
    --vector->size;
}

void vector_insert(Vector *vector, void *ptr, size_t index)
{
    size_t i;

    if (!vector || index > vector->size)
        return ;
    if (!vector_ensure_capacity(vector, vector->size + 1))
        return ;
    i = vector->size;
    while (i > index)
    {
        vector->root[i] = vector->root[i - 1];
        --i;
    }
    vector->root[index] = ptr;
    ++vector->size;
}

void vector_erase(Vector *vector, size_t index)
{
    size_t i;

    if (!vector || index >= vector->size)
        return ;
    i = index;
    while (i < vector->size - 1)
    {
        vector->root[i] = vector->root[i + 1];
        ++i;
    }
    --vector->size;
}

void vector_swap(Vector *vector, size_t index, size_t index2)
{
    void *tmp;

    if (!vector || index >= vector->size || index2 >= vector->size)
        return ;
    tmp = (vector->root)[index];
    (vector->root)[index] = (vector->root)[index2];
    (vector->root)[index2] = tmp;
}

void vector_swap_ptrs(Vector *vector, void *ptr, void *ptr2)
{
    size_t index;
    size_t index2;

    if (!vector)
        return ;
    index = vector_find(vector, ptr);
    index2 = vector_find(vector, ptr2);
    vector_swap(vector, index, index2);
}

void vector_clear(Vector *vector)
{
    if (!vector)
        return ;
    vector->size = 0;
}
