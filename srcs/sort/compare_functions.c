/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* Branch-based comparison (no subtraction) so it stays correct across
** the full range of each type without overflow or truncation. */
int compare_int(const void *a, const void *b)
{
    int av = *(const int *)a;
    int bv = *(const int *)b;

    return ((av > bv) - (av < bv));
}

int compare_char(const void *a, const void *b)
{
    char av = *(const char *)a;
    char bv = *(const char *)b;

    return ((av > bv) - (av < bv));
}

int compare_str(const void *a, const void *b)
{
    return (ft_strcmp(*(char * const *)a, *(char * const *)b));
}

int compare_double(const void *a, const void *b)
{
    double av = *(const double *)a;
    double bv = *(const double *)b;

    return ((av > bv) - (av < bv));
}

int compare_float(const void *a, const void *b)
{
    float av = *(const float *)a;
    float bv = *(const float *)b;

    return ((av > bv) - (av < bv));
}

int compare_long(const void *a, const void *b)
{
    long av = *(const long *)a;
    long bv = *(const long *)b;

    return ((av > bv) - (av < bv));
}

int compare_ulong(const void *a, const void *b)
{
    unsigned long av = *(const unsigned long *)a;
    unsigned long bv = *(const unsigned long *)b;

    return ((av > bv) - (av < bv));
}

int compare_llong(const void *a, const void *b)
{
    long long av = *(const long long *)a;
    long long bv = *(const long long *)b;

    return ((av > bv) - (av < bv));
}

int compare_ullong(const void *a, const void *b)
{
    unsigned long long av = *(const unsigned long long *)a;
    unsigned long long bv = *(const unsigned long long *)b;

    return ((av > bv) - (av < bv));
}
