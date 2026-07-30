/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static bool add_string_to_words(char **words, char *str, size_t index)
{
    if (!(words[index] = ft_strdup(str)))
        return (false);
    words[index + 1] = NULL;
    free(str);
    return (true);
}

/* splits `src` on `sep` into `words` (caller-sized, NULL-terminated);
** returns `src` itself unchanged */
char *ft_strsplit(char *src, char **words, const char *sep)
{
    char    *to_add;
    size_t  j;
    size_t  i;

    if (!src || !words)
        return (NULL);
    to_add = NULL;
    j = 0;
    i = 0;
    while (src[i])
    {
        if (!ft_strsncmp(&src[i], sep, 0, ft_strlen(sep)))
        {
            if (to_add)
            {
                if (!add_string_to_words(words, to_add, j))
                    return (NULL);
                to_add = NULL;
                ++j;
                i += ft_strlen(sep) - 1;
            }
            else
                ++i;
        }
        else
            to_add = ft_fstrcjoin(to_add, src[i]);
        ++i;
    }
    if (to_add && !add_string_to_words(words, to_add, j))
        return (NULL);
    return (src);
}
