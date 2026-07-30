/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_internal.h"
#include <crypto.h>

/* Introsort: median-of-3-random pivot, 3-way partitioning, insertion-sort
** cutoff for small ranges, and a depth-limited fallback to heapsort to
** bound the worst case at O(n log n). */
#define QSORT_INSERTION_CUTOFF 16

typedef struct s_qsort_ctx
{
    size_t          elem_size;
    CompareFunc     compare;
    char            *pivot_buf;
    char            *swap_buf;
    unsigned int    rng_state;
}   t_qsort_ctx;

static unsigned int xorshift32(unsigned int *state)
{
    unsigned int x;

    x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return (x);
}

static size_t random_index(t_qsort_ctx *ctx, size_t lo, size_t hi)
{
    return (lo + xorshift32(&ctx->rng_state) % (hi - lo + 1));
}

static size_t median_of_three_random(t_qsort_ctx *ctx, char *arr, size_t lo,
        size_t hi)
{
    size_t  i1;
    size_t  i2;
    size_t  i3;
    size_t  tmp;

    i1 = random_index(ctx, lo, hi);
    i2 = random_index(ctx, lo, hi);
    i3 = random_index(ctx, lo, hi);
    if (ctx->compare(arr + i1 * ctx->elem_size, arr + i2 * ctx->elem_size) > 0)
    {
        tmp = i1;
        i1 = i2;
        i2 = tmp;
    }
    if (ctx->compare(arr + i2 * ctx->elem_size, arr + i3 * ctx->elem_size) > 0)
    {
        tmp = i2;
        i2 = i3;
        i3 = tmp;
    }
    if (ctx->compare(arr + i1 * ctx->elem_size, arr + i2 * ctx->elem_size) > 0)
    {
        tmp = i1;
        i1 = i2;
        i2 = tmp;
    }
    return (i2);
}

static int ilog2_size(size_t n)
{
    int result;

    result = 0;
    while (n > 1)
    {
        n >>= 1;
        ++result;
    }
    return (result);
}

/* Dutch national flag 3-way partition: after this call,
** arr[lo..lt-1] < pivot, arr[lt..gt] == pivot, arr[gt+1..hi] > pivot. */
static size_t three_way_partition(t_qsort_ctx *ctx, char *arr, size_t lo,
        size_t hi, size_t *out_gt)
{
    size_t  pivot_idx;
    size_t  lt;
    size_t  i;
    size_t  gt;
    int     cmp;

    pivot_idx = median_of_three_random(ctx, arr, lo, hi);
    ft_memcpy(ctx->pivot_buf, arr + pivot_idx * ctx->elem_size,
        ctx->elem_size);
    lt = lo;
    i = lo;
    gt = hi;
    while (i <= gt)
    {
        cmp = ctx->compare(arr + i * ctx->elem_size, ctx->pivot_buf);
        if (cmp < 0)
        {
            sort_swap(arr + lt * ctx->elem_size, arr + i * ctx->elem_size,
                ctx->elem_size, ctx->swap_buf);
            ++lt;
            ++i;
        }
        else if (cmp > 0)
        {
            sort_swap(arr + i * ctx->elem_size, arr + gt * ctx->elem_size,
                ctx->elem_size, ctx->swap_buf);
            if (gt == lo)
                break ;
            --gt;
        }
        else
            ++i;
    }
    *out_gt = gt;
    return (lt);
}

static void introsort(t_qsort_ctx *ctx, char *arr, size_t lo, size_t hi,
        int depth_limit)
{
    size_t  lt;
    size_t  gt;
    size_t  left_size;
    size_t  right_size;

    while (hi > lo)
    {
        if (hi - lo + 1 <= QSORT_INSERTION_CUTOFF)
        {
            sort_insertion_range(arr, lo, hi, ctx->elem_size, ctx->compare,
                ctx->pivot_buf);
            return ;
        }
        if (depth_limit <= 0)
        {
            sort_heapsort_range(arr, lo, hi, ctx->elem_size, ctx->compare,
                ctx->swap_buf);
            return ;
        }
        --depth_limit;
        lt = three_way_partition(ctx, arr, lo, hi, &gt);
        left_size = lt - lo;
        right_size = (gt < hi) ? hi - gt : 0;
        if (left_size < right_size)
        {
            if (left_size > 0)
                introsort(ctx, arr, lo, lt - 1, depth_limit);
            if (right_size == 0)
                return ;
            lo = gt + 1;
        }
        else
        {
            if (right_size > 0)
                introsort(ctx, arr, gt + 1, hi, depth_limit);
            if (left_size == 0)
                return ;
            hi = lt - 1;
        }
    }
}

void ft_qsort(void *array, size_t size, size_t elem_size, CompareFunc compare)
{
    t_qsort_ctx     ctx;
    unsigned int    seed;

    if (size < 2 || !array || !compare)
        return ;
    if (!(ctx.pivot_buf = malloc(elem_size)))
        return ;
    if (!(ctx.swap_buf = malloc(elem_size)))
    {
        free(ctx.pivot_buf);
        return ;
    }
    seed = (unsigned int)ft_secure_random();
    if (seed == 0)
        seed = 0x9e3779b9u;
    ctx.elem_size = elem_size;
    ctx.compare = compare;
    ctx.rng_state = seed;
    introsort(&ctx, (char *)array, 0, size - 1, 2 * ilog2_size(size));
    free(ctx.pivot_buf);
    free(ctx.swap_buf);
}
