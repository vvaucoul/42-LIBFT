/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include <stdarg.h>

/* Amortized O(1) capacity-doubling grow, shared by the options array, the
** sorted long-name index, and the positional-argument array. */
void *parser_grow(void *array, size_t *capacity, size_t elem_size,
        size_t needed)
{
    size_t  new_capacity;
    void    *new_array;

    if (needed <= *capacity)
        return (array);
    new_capacity = *capacity == 0 ? 4 : *capacity * 2;
    while (new_capacity < needed)
        new_capacity *= 2;
    if (!(new_array = ft_realloc(array, new_capacity * elem_size)))
        return (NULL);
    *capacity = new_capacity;
    return (new_array);
}

/* O(1): a direct index into a 128-slot table, one per possible `char`. */
t_parser_option *parser_find_short(t_parser *parser, char c)
{
    if (!parser || c == '\0')
        return (NULL);
    return (parser->short_index[(unsigned char)c]);
}

/* O(log n) binary search over long_index, kept sorted by long_name as
** options are registered (see parser_add_option()). */
t_parser_option *parser_find_long(t_parser *parser, const char *name)
{
    size_t  lo;
    size_t  hi;
    size_t  mid;
    int     cmp;

    if (!parser || !name)
        return (NULL);
    lo = 0;
    hi = parser->long_index_count;
    while (lo < hi)
    {
        mid = lo + (hi - lo) / 2;
        cmp = ft_strcmp(parser->long_index[mid]->long_name, name);
        if (cmp == 0)
            return (parser->long_index[mid]);
        if (cmp < 0)
            lo = mid + 1;
        else
            hi = mid;
    }
    return (NULL);
}

void parser_set_error(t_parser *parser, const char *fmt, ...)
{
    va_list args;

    if (!parser)
        return ;
    parser->has_error = true;
    va_start(args, fmt);
    vsnprintf(parser->error, sizeof(parser->error), fmt, args);
    va_end(args);
}

/* Strict integer parsing: optional sign, at least one digit, nothing else -
** garbage input ("12abc") is rejected rather than truncated. */
bool parser_str_to_long(const char *str, long *out)
{
    bool    is_neg;
    long    result;
    size_t  i;

    if (!str || !str[0])
        return (false);
    i = 0;
    is_neg = false;
    if (str[i] == '-' || str[i] == '+')
        is_neg = (str[i++] == '-');
    if (!ft_isdigit(str[i]))
        return (false);
    result = 0;
    while (ft_isdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        ++i;
    }
    if (str[i] != '\0')
        return (false);
    *out = is_neg ? -result : result;
    return (true);
}
