/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 09:46:24 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/10 10:02:51 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*******************************************************************************
 *                                   STRINGS                                   *
 ******************************************************************************/

/*
**	ft_fstrcjoin: concatenate a char to a string and free str
**  @s1: string reference
**  @c: char to concatenate
**  @return: the new string
*/

char *ft_fstrcjoin(char *str, char c)
{
    char *new_str = NULL;
    size_t len;

    if (!str)
    {
        if (!(new_str = ft_calloc(sizeof(char), 2)))
            return (NULL);
        new_str[0] = c;
        return (new_str);
    }
    else
    {
        len = ft_strlen(str);
        if (!(new_str = ft_calloc(sizeof(char), len + 2)))
            return (NULL);
        ft_memcpy(new_str, str, len);
        new_str[len] = c;
        free(str);
    }
    return (new_str);
}

/*
**  ft_fstrjoin: concatenate a string to a string and free str
**  @s1: string reference
**  @s2: string to concatenate
**  @return: the new string
*/

char *ft_fstrjoin(char *str, const char *join)
{
    char *new_str = NULL;

    if (!(new_str = ft_strjoin(str, join)))
        return (NULL);
    free(str);
    return (new_str);
}

/*
**  ft_lentc: get the length of a string to a char
**  @s: string to get the length
**  @c: char to find
**  @return: the length of the string to the char
*/

size_t ft_lentc(const char *str, char c)
{
    if (!str)
        return (0);
    if (!ft_ccof(c, str))
        return (0);
    for (size_t i = 0; str[i]; ++i)
    {
        if (str[i] == c)
            return (i);
    }
    return (ft_strlen(str));
}

/*
**  ft_lents: get the length of a string to a string
**  @s: string to get the length
**  @s2: string to find
**  @return: the length of the string to the string
*/

size_t ft_lents(const char *str, const char *cmp)
{
    size_t len = 0;

    if (!str || !cmp)
        return (0);

    len = ft_strlen(cmp);
    for (size_t i = 0; str[i]; ++i)
    {
        if (!ft_strncmp(&str[i], cmp, len))
            return (i);
    }
    return (ft_strlen(str));
}

/*
**  ft_multijoin: concatenate an array of strings to a string
**  @arr: array of strings to concatenate
**  @return: the new string
*/

char *ft_multijoin(const char **array)
{
    char *new_str = NULL;
    size_t i = 0;

    if (!array)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), ft_asize(array))))
        return (NULL);
    while (array[i])
    {
        if (!(new_str = ft_fstrjoin(new_str, array[i])))
            return (NULL);
        ++i;
    }
    return (new_str);
}

/*
**  ft_scof: check if string contains anoter string
**  @s: string to check
**  @s2: string to find
**  @return: 1 if the string contains the string, 0 otherwise
*/

bool ft_scof(const char *str, const char *cmp)
{
    if (!str || !cmp)
        return (false);
    for (size_t i = 0; str[i]; ++i)
    {
        for (size_t j = 0; cmp[j]; ++j)
        {
            if (str[i] == cmp[j])
                return (true);
        }
    }
    return (false);
}

/*
**  ft_sncof: check if string contains anoter string with a given length
**  @s: string to check
**  @s2: string to find
**  @len: length max
**  @return: 1 if the string contains the string, 0 otherwise
*/

bool ft_sncof(const char *str, const char *cmp, size_t len)
{
    if (!str || !cmp)
        return (false);
    for (size_t i = 0; str[i] && i < len; ++i)
    {
        for (size_t j = 0; cmp[j]; ++j)
        {
            if (str[i] == cmp[j])
                return (true);
        }
    }
    return (false);
}

/*
**  ft_strchr: find the first occurence of a char in a string
**  @s: string to search
**  @c: char to find
**  @return: the first occurence of the char in the string
*/

char *ft_strchr(const char *str, int c)
{
    char *tmp;
    if (!str)
        return (NULL);
    tmp = (char *)str;
    for (size_t i = 0; str[i]; ++i)
    {
        if (str[i] == c)
            return (tmp);
        ++tmp;
    }
    if (!c)
        return (tmp);
    return (NULL);
}

/*
**  ft_strcjoin: concatenate a char to a string
**  @s1: string reference
**  @c: char to concatenate
**  @return: the new string
*/

char *ft_strcjoin(char *str, char c)
{
    char *new_str = NULL;
    size_t len;

    if (!str)
    {
        if (!(new_str = ft_calloc(sizeof(char), 2)))
            return (NULL);
        new_str[0] = c;
        return (new_str);
    }
    else
    {
        len = ft_strlen(str);
        if (!(new_str = ft_calloc(sizeof(char), len + 2)))
            return (NULL);
        ft_memcpy(new_str, str, len);
        new_str[len] = c;
    }
    return (new_str);
}

/*
**  ft_strcmp: compare two strings
**  @s1: string to compare
**  @s2: string to compare
**  @return: the result of the comparison
*/

int ft_strcmp(const char *str, const char *str2)
{
    unsigned int i;

    i = 0;
    while (str[i] && str[i] == str2[i])
        ++i;
    return ((unsigned char)str[i] - (unsigned char)str2[i]);
}

/*
**  ft_strcpy: copy a string to another string
**  @s1: new string
**  @s2: string to copy
**  @return: the new string
*/

char *ft_strcpy(char *dest, const char *str)
{
    if (str)
        return (NULL);
    else if (!dest)
    {
        if (!(dest = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
            return (NULL);
    }
    for (size_t i = 0; str[i]; ++i)
        dest[i] = str[i];
    dest[ft_strlen(str)] = '\0';
    return (dest);
}

char *ft_strdup(const char *str)
{
    char *new_str = NULL;

    if (!str)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), ft_strlen(str))))
        return (NULL);
    for (size_t i = 0; str[i]; ++i)
        new_str[i] = str[i];
    return (new_str);
}

char *ft_strjoin(const char *str, const char *join)
{
    char *new_str = NULL;
    size_t i = 0, j = 0, length = 0;

    if (!str)
        return (NULL);
    if (!join)
        return ((char *)str);

    length = ft_strlen(str) + ft_strlen(join) + 1;
    if (!(new_str = ft_calloc(sizeof(char), length)))
        return (NULL);
    ft_bzero(new_str, length);
    for (; str[i]; ++i)
        new_str[i] = str[i];
    for (; join[j]; ++j)
        new_str[i + j] = join[j];
    return (new_str);
}

size_t ft_strlen(const char *str)
{
    size_t i = 0;

    while (str[i])
        ++i;
    return (i);
}

char *ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
    char *new_str;
    int i;

    if (!str)
        return (NULL);
    i = 0;
    if (!(new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
        return (NULL);
    while (str[i])
    {
        new_str[i] = (*f)(i, str[i]);
        ++i;
    }
    return (new_str);
}

int ft_strncmp(const char *str, const char *str2, size_t len)
{
    unsigned long int i;

    if (len == 0)
        return (0);
    i = 0;
    while (i < len && (unsigned char)str[i] == (unsigned char)str2[i])
    {
        if (((unsigned char)str[i] == 0 &&
             (unsigned char)str2[i] == 0) ||
            i == (len - 1))
            return (0);
        ++i;
    }
    return ((unsigned char)str[i] - (unsigned char)str2[i]);
}

char *ft_strncpy(const char *str, size_t len)
{
    char *new_str;

    if (!str)
        return (NULL);
    if (ft_strlen(str) < len)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), len + 1)))
        return (NULL);
    for (size_t i = 0; str[i] && i < len; ++i)
        new_str[i] = str[i];
    return (new_str);
}

char *ft_strrdbls(const char *str, char c)
{
    char *new_str = NULL;
    size_t j = 0;
    int pass = 0;

    if (!str)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
        return (NULL);
    for (size_t i = 0; str[i]; ++i)
    {
        if (str[i] != c)
        {
            new_str[j] = str[i];
            ++j;
            pass = 0;
        }
        else
        {
            if (pass == 0)
            {
                new_str[j] = str[i];
                ++j;
            }
            ++pass;
        }
    }
    free((char *)str);
    return (new_str);
}

char *ft_strremove(const char *str, char c)
{
    char *new_str = NULL;
    size_t j = 0;

    if (!str)
        return (NULL);
    if (!(new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1)))
        return (NULL);
    for (size_t i = 0; str[i]; ++i)
    {
        if (str[i] != c)
        {
            new_str[j] = str[i];
            ++j;
        }
    }
    free((char *)str);
    return (new_str);
}

char *ft_strrep(char *src, const char *pat, const char *new_pat)
{
    char *new_str = NULL;
    size_t len;

    if (!pat || !new_pat || !src)
        return (NULL);
    len = ft_strlen(src);
    if (!(new_str = ft_calloc(sizeof(char), len + ft_strlen(new_pat) + 1)))
        return (NULL);
    if (ft_scof(src, pat) == false)
        return (NULL);
    for (size_t i = 0; src[i]; ++i)
    {
        if (!ft_strncmp(&src[i], pat, ft_strlen(pat)))
        {
            new_str = ft_fstrjoin(new_str, new_pat);
            i += ft_strlen(pat) - 1;
        }
        else
            new_str = ft_fstrcjoin(new_str, src[i]);
    }
    free(src);
    src = new_str;
    return (new_str);
}

int ft_strsncmp(const char *str, const char *cmp, size_t start, size_t len)
{
    if (!len)
        return (0);
    if (!str || !cmp)
        return (0);
    if (start > ft_strlen(str))
        return (0);

    size_t i = start;
    for (; str[i] == cmp[i]; ++i)
    {
        if ((!str[i] && !cmp[i]) || i == (len - 1))
            return (0);
    }
    return (str[i] - cmp[i]);
}

static bool add_string_to_words(char **words, char *str, size_t index)
{
    if (!(words[index] = ft_strdup(str)))
        return (false);
    words[index + 1] = NULL;
    free(str);
    str = NULL;
    return (true);
}

char *ft_strsplit(char *src, char **words, const char *sep)
{
    char *to_add = NULL;
    size_t j = 0;

    if (!src)
        return (NULL);
    if (!words)
        return (NULL);
    for (size_t i = 0; src[i]; ++i)
    {
        if (!ft_strsncmp(&src[i], sep, 0, ft_strlen(sep)))
        {
            if (to_add)
            {
                if (!(add_string_to_words(words, to_add, j)))
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
    }
    if (to_add)
    {
        if (!(add_string_to_words(words, to_add, j)))
            return (NULL);
        to_add = NULL;
    }
    return (src);
}

char *ft_strtrim(char *str)
{
    if (!str)
        return (NULL);
    for (size_t i = 0; str[i]; ++i)
    {
        while (ft_isspace(str[i]))
            ft_memmove((char *)&str[i], (char *)&str[i + 1], ft_strlen(str) - i);
    }
    return (str);
}

char *ft_strzap(char *str, const char *pat)
{
    size_t j = 0;
    char *new_str = NULL;

    if (!str || !pat)
        return (NULL);
    if (ft_strlen(str) < ft_strlen(pat))
        return (str);
    if (!ft_strsncmp(str, pat, 0, ft_strlen(pat)))
    {
        if (!(new_str = ft_calloc(sizeof(char), (ft_strlen(str) - ft_strlen(pat)) + 1)))
            return (NULL);
        for (size_t i = ft_strlen(pat); str[i]; ++i)
        {
            new_str[j] = str[i];
            ++j;
        }
        free(str);
        str = new_str;
        return (new_str);
    }
    return (str);
}

char *ft_substr(char *str, size_t start, size_t len)
{
    char *new_str = NULL;
    size_t j = 0;

    if (!str)
        return (NULL);
    if (len > ft_strlen(str) || start > ft_strlen(str))
        return (str);
    if (!(new_str = ft_calloc(sizeof(char), len + 1)))
        return (NULL);
    for (size_t i = start; str[i] && i < len; ++i)
    {
        new_str[j] = str[i];
        ++j;
    }
    free(str);
    return (new_str);
}