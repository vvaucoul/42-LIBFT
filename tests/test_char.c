/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(char, isalpha_letters)
{
	int c;

	c = 'a';
	while (c <= 'z')
	{
		ASSERT_MSG(ft_isalpha(c) == true, "ft_isalpha('%c') should be true", c);
		++c;
	}
	c = 'A';
	while (c <= 'Z')
	{
		ASSERT_MSG(ft_isalpha(c) == true, "ft_isalpha('%c') should be true", c);
		++c;
	}
}

TEST(char, isalpha_non_letters)
{
	ASSERT(ft_isalpha('0') == false);
	ASSERT(ft_isalpha('9') == false);
	ASSERT(ft_isalpha(' ') == false);
	ASSERT(ft_isalpha('@') == false);
	ASSERT(ft_isalpha('[') == false);
	ASSERT(ft_isalpha('`') == false);
	ASSERT(ft_isalpha('{') == false);
	ASSERT(ft_isalpha(0) == false);
	ASSERT(ft_isalpha(-1) == false);
}

TEST(char, isdigit)
{
	int c;

	c = '0';
	while (c <= '9')
	{
		ASSERT(ft_isdigit(c) == true);
		++c;
	}
	ASSERT(ft_isdigit('/') == false);
	ASSERT(ft_isdigit(':') == false);
	ASSERT(ft_isdigit('a') == false);
	ASSERT(ft_isdigit(-1) == false);
}

TEST(char, isalnum)
{
	ASSERT(ft_isalnum('a') == true);
	ASSERT(ft_isalnum('Z') == true);
	ASSERT(ft_isalnum('5') == true);
	ASSERT(ft_isalnum(' ') == false);
	ASSERT(ft_isalnum('_') == false);
	ASSERT(ft_isalnum('!') == false);
}

TEST(char, isascii)
{
	ASSERT(ft_isascii(0) == true);
	ASSERT(ft_isascii(127) == true);
	ASSERT(ft_isascii(65) == true);
	ASSERT(ft_isascii(128) == false);
	ASSERT(ft_isascii(255) == false);
	ASSERT(ft_isascii(-1) == false);
}

TEST(char, isupper_islower)
{
	ASSERT(ft_isupper('A') == true);
	ASSERT(ft_isupper('Z') == true);
	ASSERT(ft_isupper('a') == false);
	ASSERT(ft_isupper('9') == false);
	ASSERT(ft_islower('a') == true);
	ASSERT(ft_islower('z') == true);
	ASSERT(ft_islower('A') == false);
	ASSERT(ft_islower('9') == false);
}

TEST(char, isspace_matches_libc_whitespace)
{
	ASSERT(ft_isspace(' ') == true);
	ASSERT(ft_isspace('\t') == true);
	ASSERT(ft_isspace('\n') == true);
	ASSERT(ft_isspace('\v') == true);
	ASSERT(ft_isspace('\f') == true);
	ASSERT(ft_isspace('\r') == true);
	ASSERT(ft_isspace('a') == false);
	ASSERT(ft_isspace('0') == false);
}

TEST(char, toupper_tolower)
{
	ASSERT_EQ_INT(ft_toupper('a'), 'A');
	ASSERT_EQ_INT(ft_toupper('z'), 'Z');
	ASSERT_EQ_INT(ft_toupper('A'), 'A');
	ASSERT_EQ_INT(ft_toupper('5'), '5');
	ASSERT_EQ_INT(ft_toupper(' '), ' ');
	ASSERT_EQ_INT(ft_tolower('A'), 'a');
	ASSERT_EQ_INT(ft_tolower('Z'), 'z');
	ASSERT_EQ_INT(ft_tolower('a'), 'a');
	ASSERT_EQ_INT(ft_tolower('5'), '5');
}

TEST(char, ccof_found_and_not_found)
{
	ASSERT(ft_ccof('a', "abc") == true);
	ASSERT(ft_ccof('c', "abc") == true);
	ASSERT(ft_ccof('z', "abc") == false);
	ASSERT(ft_ccof('a', "") == false);
	ASSERT(ft_ccof('a', NULL) == false);
}

TEST(char, isxdigit_hex_digits)
{
	ASSERT(ft_isxdigit('0') == true);
	ASSERT(ft_isxdigit('9') == true);
	ASSERT(ft_isxdigit('a') == true);
	ASSERT(ft_isxdigit('f') == true);
	ASSERT(ft_isxdigit('A') == true);
	ASSERT(ft_isxdigit('F') == true);
	ASSERT(ft_isxdigit('g') == false);
	ASSERT(ft_isxdigit('G') == false);
	ASSERT(ft_isxdigit(' ') == false);
}

TEST(char, iscntrl_control_characters)
{
	ASSERT(ft_iscntrl('\0') == true);
	ASSERT(ft_iscntrl('\n') == true);
	ASSERT(ft_iscntrl('\t') == true);
	ASSERT(ft_iscntrl(127) == true);
	ASSERT(ft_iscntrl('a') == false);
	ASSERT(ft_iscntrl(' ') == false);
}

TEST(char, isprint_printable_including_space)
{
	ASSERT(ft_isprint(' ') == true);
	ASSERT(ft_isprint('a') == true);
	ASSERT(ft_isprint('~') == true);
	ASSERT(ft_isprint('\n') == false);
	ASSERT(ft_isprint(127) == false);
}

TEST(char, isgraph_printable_excluding_space)
{
	ASSERT(ft_isgraph('a') == true);
	ASSERT(ft_isgraph('!') == true);
	ASSERT(ft_isgraph(' ') == false);
	ASSERT(ft_isgraph('\n') == false);
}

TEST(char, ispunct_punctuation_only)
{
	ASSERT(ft_ispunct('.') == true);
	ASSERT(ft_ispunct(',') == true);
	ASSERT(ft_ispunct('!') == true);
	ASSERT(ft_ispunct('a') == false);
	ASSERT(ft_ispunct('5') == false);
	ASSERT(ft_ispunct(' ') == false);
}
