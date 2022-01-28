/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:18:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/01/28 02:21:04 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

        char ptr3[10];

        ft_bzero(ptr3, 10);
        ft_memset(ptr3, 'A', 9);
        ft_memlower(ptr3, 9);
        ft_printf("- MemLower [%s]\n", ptr3);
        ft_memupper(ptr3, 9);
        ft_printf("- MemUpper [%s]\n\n", ptr3);
        
        ft_printf("- MemLen [%d] [%d]\n", ft_memlen(ptr3), ft_memlen(ptr));
    }

    return (0);
}
