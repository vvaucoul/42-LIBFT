/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strzap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* strips `pat` from the front of `str` only as a literal prefix (not
** "anywhere in the string" despite the generic name). */
char *ft_strzap(char *str, const char *pat)
{
    char    *new_str;
    size_t  pat_len;
    size_t  i;
    size_t  j;

    if (!str || !pat)
        return (NULL);
    pat_len = ft_strlen(pat);
    if (ft_strlen(str) < pat_len)
        return (str);
    if (ft_strsncmp(str, pat, 0, pat_len))
        return (str);
    if (!(new_str = ft_calloc(sizeof(char), ft_strlen(str) - pat_len + 1)))
        return (NULL);
    j = 0;
    i = pat_len;
    while (str[i])
    {
        new_str[j] = str[i];
        ++j;
        ++i;
    }
    free(str);
    return (new_str);
}
