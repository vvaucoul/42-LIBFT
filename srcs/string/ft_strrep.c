/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* replaces every occurrence of `pat` in `src` with `new_pat` (frees src) */
char *ft_strrep(char *src, const char *pat, const char *new_pat)
{
    char    *new_str;
    size_t  pat_len;
    size_t  i;

    if (!pat || !new_pat || !src)
        return (NULL);
    pat_len = ft_strlen(pat);
    if (pat_len == 0 || ft_lents(src, pat) == ft_strlen(src))
        return (src);
    if (!(new_str = ft_calloc(sizeof(char), 1)))
        return (NULL);
    i = 0;
    while (src[i])
    {
        if (!ft_strncmp(&src[i], pat, pat_len))
        {
            new_str = ft_fstrjoin(new_str, new_pat);
            i += pat_len - 1;
        }
        else
            new_str = ft_fstrcjoin(new_str, src[i]);
        ++i;
    }
    free(src);
    return (new_str);
}
