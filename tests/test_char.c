/* ************************************************************************** */
/*   test_char.c - srcs/char/ *.c                                             */
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

/* ft_isspace only recognizes ' ' (0x20) - unlike the standard C isspace()
** it does NOT treat \t \n \v \f \r as whitespace. Documenting the actual
** implemented behavior here, not the libc contract. */
TEST(char, isspace_space_only)
{
	ASSERT(ft_isspace(' ') == true);
	ASSERT(ft_isspace('\t') == false);
	ASSERT(ft_isspace('\n') == false);
	ASSERT(ft_isspace('\v') == false);
	ASSERT(ft_isspace('\f') == false);
	ASSERT(ft_isspace('\r') == false);
	ASSERT(ft_isspace('a') == false);
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
