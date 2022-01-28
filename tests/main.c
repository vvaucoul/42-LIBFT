/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:18:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 19:13:35 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int main(int argc, char const *argv[])
{
    ft_printf("- FT_Putchar: ");
    ft_putchar('4');
    ft_putchar('\n');

    ft_printf("- FT_Putendl: ");
    ft_putendl("42Born2Code");

    ft_printf("- FT_Putstr: ");
    ft_putstr("42Born2Code\n");

    ft_printf("- FT_Putnbr: ");
    ft_putnbr(42);
    ft_putchar('\n');

    ft_printf("\n### PRINTF ###\n\n");

    ft_printf("Test D [%d]\n", 42);
    ft_printf("Test I [%i]\n", 42);
    ft_printf("Test S [%s]\n", "42Born2Code");

    ft_printf("- NBR Len [0]: [%d]\n", ft_nbrlen(0));
    ft_printf("- NBR Len [42]: [%d]\n", ft_nbrlen(42));
    ft_printf("- NBR Len [2147483647]: [%d]\n", ft_nbrlen(2147483647));

    ft_printf("\n### ALLOC ###\n\n");

    {
        char *ptr = malloc(100);
        char *ptr2 = malloc(500);
        char *ptr3 = malloc(1000);
        ft_multifree((void *[]){ptr, ptr2, ptr3, NULL});
    }

    ft_printf("\n### MEMORY ###\n\n");
    {
        char ptr[42], ptr2[42];

        ft_bzero(ptr, 42);
        ft_bzero(ptr2, 42);
        ft_printf("- Bzero [%s]\n", ptr);
        ft_printf("- Bzero [%s]\n\n", ptr2);

        ft_memset(ptr, 'c', 10);
        ft_memset(ptr2, 'd', 10);
        ft_printf("- Memset [%s]\n", ptr);
        ft_printf("- Memset [%s]\n", ptr2);

        ft_memcpy(ptr2, ptr, 10);
        ft_printf("- Memcpy [%s]\n", ptr);
        ft_printf("- Memcpy [%s]\n\n", ptr2);

        char ptr3[10], ptr4[13];

        ft_bzero(ptr3, 10);
        ft_memset(ptr3, 'A', 9);
        ft_memlower(ptr3, 9);
        ft_printf("- MemLower [%s]\n", ptr3);
        ft_memupper(ptr3, 9);
        ft_printf("- MemUpper [%s]\n\n", ptr3);

        ft_bzero(ptr4, 14);
        ft_memcpy(ptr4, "42Born2Code", 13);
        ft_memcrm(ptr4, '2', 13);
        ft_printf("- Memcrm [%s]\n", ptr4);
        ft_memcpy(ptr4, "42Born2Code", 13);
        ft_memsrm(ptr4, "42", 13);
        ft_printf("- Memsrm [%s]\n\n", ptr4);

        ft_memcpy(ptr4, "42Born2Code", 13);
        ft_swap((int *)&ptr4[0], (int *)&ptr4[3]);
        ft_printf("- ft_swap [%s]\n", ptr4);

        ft_memcpy(ptr4, "42Born2Code", 13);
        ft_vswap((void *)&ptr4[0], (void *)&ptr4[3]);
        ft_printf("- ft_vswap [%s]\n", ptr4);

        ft_memcpy(ptr3, "42Born2Code", 9);
        ft_memcpy(ptr4, "42Born2Code", 13);

        ft_printf("- PTR3 [%s] | PTR4 [%s]\n", ptr3, ptr4);
        ft_printf("- Memcmp [%d]\n", ft_memcmp(ptr3, ptr4, 9));
        ft_swap((int *)&ptr3[0], (int *)&ptr3[4]);
        ft_printf("- PTR3 [%s] | PTR4 [%s]\n", ptr3, ptr4);
        ft_printf("- Memcmp [%d]\n", ft_memcmp(ptr3, ptr4, 9));

        ft_memcpy(ptr3, "42Born4Code", 9);
        ft_memcpy(ptr4, "42Born2Code", 13);
        ft_printf("- PTR3 [%s] | PTR4 [%s]\n", ptr3, ptr4);
        ft_printf("- Memscmp [%d]\n", ft_memscmp(ptr3, ptr4, 9, 7));
        ft_printf("- Memscmp [%d]\n\n", ft_memscmp(ptr3, ptr4, 9, 0));

        ft_memcpy(ptr4, "42Born2Code", 13);
        ft_printf("- Memchr [%s]\n", ft_memchr(ptr4, '2', 13));
        ft_printf("- Memchr [%s]\n", ft_memchr(ptr4, 'C', 13));

        ft_memcpy(ptr4, "42Born2Code", 13);
        ft_printf("- Memshr [%s]\n", ft_memshr(ptr4, "42", 13, 2));
        ft_printf("- Memshr [%s]\n", ft_memshr(ptr4, "Co", 13, 2));
        ft_printf("- Memshr [%s]\n", ft_memshr(ptr4, "Born2Code", 13, 10));

        void *m_ptr = NULL;

        ft_memcpy(ptr4, "42Born2Code", 13);
        ft_memalloc((void *)&m_ptr, ptr4, sizeof(char), 13);
        ft_printf("- Memalloc [%s]\n", m_ptr);
        free(m_ptr);

        char ptr5[13], ptr6[13];

        ft_bzero(ptr5, 13);
        ft_bzero(ptr6, 13);
        ft_memcpy(ptr5, "42Born2Code", 12);
        printf("- ft_memmove: PTR5 [%s] | PTR6 [%s]\n", ptr5, ptr6);
        ft_memmove(ptr6, ptr5, 12);
        printf("- ft_memmove: PTR5 [%s] | PTR6 [%s]\n", ptr5, ptr6);

        ft_memcpy(ptr5, "42Born2Code", 12);
        ft_memmove(ptr6, &ptr5[6], 6);

        printf("- ft_memmove: PTR5 [%s] | PTR6 [%s]\n", ptr5, ptr6);
        ft_printf("\n\n");
    }

    char *str = ft_strdup("42Born2Code");
    char *str2 = ft_strdup("42Born4Code");
    ft_printf("- STR [%s] | STR2 [%s]\n", str, str2);

    ft_printf("- STRcmp [%d]\n", ft_strcmp(str, str2));
    ft_memcpy(str, "42Born2Code", 12);
    ft_memcpy(str2, "42Born2Code", 12);
    ft_printf("- STRcmp [%d]\n", ft_strcmp(str, str2));
    ft_memcpy(str, "42Born4Code", 12);
    ft_memcpy(str2, "42Born2Code", 12);
    ft_printf("- STRcmp [%d]\n\n", ft_strcmp(str, str2));

    free(str);
    free(str2);

    str = ft_strdup("42Born2Code");
    str2 = ft_strcpy(str);
    ft_printf("- STRcpy [%s]\n", str2);
    free(str);
    free(str2);

    str = ft_strdup("42Born2Code");
    ft_printf("- ft_strchr: [%s]\n", ft_strchr(str, 'n'));
    ft_printf("- ft_strchr: [%s]\n", ft_strchr(str, '2'));
    ft_printf("- ft_strchr: [%s]\n", ft_strchr(str, 2));
    ft_printf("- ft_strchr: [%s]\n", ft_strchr(str, 0));
    free(str);

    void *tmp = NULL;
    ft_printf("- ft_strjoin: [%s]\n", tmp = ft_strjoin("42", "Born2Code"));
    free(tmp);
    tmp = NULL;

    ft_printf("- ft_fstrjoin: [%s]\n", tmp = ft_fstrjoin(ft_strdup("42Born"), "2Code"), "2Code");
    free(tmp);

    ft_printf("- ft_strsncmp: [%d]\n", ft_strsncmp("42Born2Code", "42Born2Code", 0, 12));
    ft_printf("- ft_strsncmp: [%d]\n", ft_strsncmp("42Born4Code", "42Born2Code", 0, 12));
    ft_printf("- ft_strsncmp: [%d]\n", ft_strsncmp("42Born4Code", "42Born2Code", 7, 12));
    ft_printf("- ft_strsncmp: [%d]\n", ft_strsncmp("42Born2Code", "42Born4Code", 6, 12));
    ft_printf("- ft_strsncmp: [%d]\n", ft_strsncmp("42Born4Code", "42Born2Code", 0, 5));

    ft_printf("- ft_strtrim: [%s]\n", ft_strtrim(tmp = ft_strdup("42 Born 2 Code")));
    free(tmp);
    ft_printf("- ft_strtrim: [%s]\n", ft_strtrim(tmp = ft_strdup("42 Born 2 Code ")));
    free(tmp);
    ft_printf("- ft_strtrim: [%s]\n\n", ft_strtrim(tmp = ft_strdup("    42 Bo    rn 2 Code ")));
    free(tmp);

    str = ft_strdup("42Born2Code");
    ft_printf("- ft_strzap: [%s]\n", str = ft_strzap(str, "42"));
    free(str);

    ft_printf("- ft_multijoin: [%s]\n", tmp = ft_multijoin((const char *[]){"42", "Born", "2", "Code", NULL}));
    free(tmp);

    char *array[15];

    ft_bzero(array, 15);
    ft_strsplit("42Born2Code", array, "2");

    ft_printf("- STRSplit: [%s] [%s]\n", "42Born2Code", "2");
    for (size_t i = 0; array[i]; ++i)
    {
        ft_printf("Array[%d] = [%s]\n", i, array[i]);
        free(array[i]);
    }

    ft_bzero(array, 15);
    ft_strsplit("42Born2Code4242TestBorn24242Code", array, "42");
    ft_printf("- STRSplit: [%s] [%s]\n", "42Born2Code4242TestBorn24242Code", "42");

    for (size_t i = 0; array[i]; ++i)
    {
        ft_printf("Array[%d] = [%s]\n", i, array[i]);
        free(array[i]);
    }

    ft_bzero(array, 15);
    ft_strsplit("42Born2Code4242TestBorn24242Code", array, "Born");
    ft_printf("- STRSplit: [%s] [%s]\n", "42Born2Code4242TestBorn24242Code", "Born");

    for (size_t i = 0; array[i]; ++i)
    {
        ft_printf("Array[%d] = [%s]\n", i, array[i]);
        free(array[i]);
    }

    str = ft_strremove(ft_strdup("42Born2Code"), '2');
    ft_printf("- ft_strremove: [%s]\n", str);
    free(str);

    str = ft_strrdbls(ft_strdup("///home///Delivery///42/str///"), '/');
    ft_printf("- ft_strrdbls: [%s]\n", str);
    free(str);

    ft_printf("ft_atoi: [%d]\n", ft_atoi("42"));
    ft_printf("ft_itoa: [%s]\n", str = ft_itoa(42));
    free(str);
    ft_printf("ft_itoa_base: [%s]\n", str = ft_itoa_base(42, 2));
    free(str);
    ft_printf("ft_itoa_base: [%s]\n", str = ft_itoa_base(42, 4));
    free(str);
    ft_printf("ft_itoa_base: [%s]\n", str = ft_itoa_base(42, 15));
    free(str);
    ft_printf("ft_itoa_base: [%s]\n", str = ft_itoa_base(42, 9));
    free(str);

    ft_printf("ft_lentc: [%d]\n", ft_lentc("42Born2Code", '2'));
    ft_printf("ft_lentc: [%d]\n", ft_lentc("42Born2Code", 'B'));
    ft_printf("ft_lentc: [%d]\n", ft_lentc("42Born2Code", 'e'));

    ft_printf("ft_lents: [%d]\n", ft_lents("42Born2Code", "42"));
    ft_printf("ft_lents: [%d]\n", ft_lents("42Born2Code", "Code"));
    ft_printf("ft_lents: [%d]\n", ft_lents("42Born2Code", "n"));
    ft_printf("ft_lents: [%d]\n\n", ft_lents("42Born2Code", "A"));

    ft_printf("ft_strrep: [%s]\n", str = ft_strrep(ft_strdup("33Born2Code"), "33", "42"));
    free(str);
    ft_printf("ft_strrep: [%s]\n", str = ft_strrep(ft_strdup("33Born33Code"), "33", "42"));
    free(str);
    ft_printf("ft_strrep: [%s]\n", str = ft_strrep(ft_strdup("TestCoucouTest123Test"), "Test", "42"));
    free(str);

    ft_printf("ft_substr: [%s]\n", str = ft_substr(ft_strdup("42Born2Code"), 2, 6));
    free(str);
    ft_printf("ft_substr: [%s]\n", str = ft_substr(ft_strdup("42Born2Code"), 7, 11));
    free(str);

    return (0);
}
