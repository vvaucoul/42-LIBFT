/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>
#include "framework/test_framework.h"

TEST(string, strlen_matches_libc)
{
	ASSERT_EQ_UINT(ft_strlen(""), 0);
	ASSERT_EQ_UINT(ft_strlen("hello"), 5);
}

TEST(string, strcmp_basic)
{
	ASSERT_EQ_INT(ft_strcmp("abc", "abc"), 0);
	ASSERT(ft_strcmp("abc", "abd") < 0);
	ASSERT(ft_strcmp("abd", "abc") > 0);
	ASSERT(ft_strcmp("ab", "abc") < 0);
}

TEST(string, strncmp_basic)
{
	ASSERT_EQ_INT(ft_strncmp("abc", "abd", 2), 0);
	ASSERT(ft_strncmp("abc", "abd", 3) != 0);
	ASSERT_EQ_INT(ft_strncmp("ab", "ab", 5), 0);
	ASSERT_EQ_INT(ft_strncmp("abcde", "abcde", 5), 0);
	ASSERT_EQ_INT(ft_strncmp("anything", "else", 0), 0);
}

TEST(string, strchr_finds_char_and_terminator)
{
	const char *s = "hello";

	ASSERT_EQ_PTR(ft_strchr(s, 'e'), s + 1);
	ASSERT_NULL(ft_strchr(s, 'z'));
	ASSERT_EQ_PTR(ft_strchr(s, '\0'), s + 5);
}

TEST(string, strcpy_copies_into_provided_buffer)
{
	char dest[16];
	char *r;

	r = ft_strcpy(dest, "hi");
	ASSERT_EQ_PTR(r, dest);
	ASSERT_EQ_STR(dest, "hi");
}

TEST(string, strcpy_null_dest_allocates_fresh_buffer)
{
	char *s = ft_strcpy(NULL, "hello");

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "hello");
	free(s);
}

TEST(string, strcpy_null_str_returns_null)
{
	char dest[4];

	ASSERT_NULL(ft_strcpy(dest, NULL));
}

TEST(string, strdup_null_terminates_correctly)
{
	char *dup = ft_strdup("hello");

	ASSERT_NOT_NULL(dup);
	ASSERT_EQ_STR(dup, "hello");
	ASSERT_EQ_INT((int)ft_strlen(dup), 5);
	free(dup);
}

TEST(string, strdup_null_returns_null)
{
	ASSERT_NULL(ft_strdup(NULL));
}

TEST(string, strncpy_first_n_chars)
{
	char *s = ft_strncpy("hello world", 5);

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "hello");
	free(s);
}

TEST(string, strncpy_len_greater_than_strlen_returns_null)
{
	ASSERT_NULL(ft_strncpy("hi", 10));
}

TEST(string, strjoin_basic)
{
	char *s = ft_strjoin("foo", "bar");

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "foobar");
	free(s);
}

TEST(string, strjoin_null_str_returns_null)
{
	ASSERT_NULL(ft_strjoin(NULL, "bar"));
}

TEST(string, strjoin_null_join_returns_str_unchanged)
{
	ASSERT_EQ_STR(ft_strjoin("foo", NULL), "foo");
}

TEST(string, fstrjoin_frees_first_argument)
{
	char *base = strdup("foo");
	char *s = ft_fstrjoin(base, "bar");

	ASSERT_EQ_STR(s, "foobar");
	free(s);
}

TEST(string, strcjoin_and_fstrcjoin_append_one_char)
{
	char *s = ft_strcjoin(NULL, 'a');

	ASSERT_EQ_STR(s, "a");
	s = ft_fstrcjoin(s, 'b');
	ASSERT_EQ_STR(s, "ab");
	free(s);
}

TEST(string, multijoin_concatenates_array)
{
	const char *arr[] = {"foo", "bar", "baz", NULL};
	char *s = ft_multijoin(arr);

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "foobarbaz");
	free(s);
}

TEST(string, scof_and_sncof_character_overlap)
{
	ASSERT(ft_scof("hello", "xyz") == false);
	ASSERT(ft_scof("hello", "leo") == true);
	ASSERT(ft_sncof("hello", "leo", 1) == false);
	ASSERT(ft_sncof("hello", "leo", 2) == true);
}

TEST(string, lentc_length_to_char)
{
	ASSERT_EQ_UINT(ft_lentc("hello.txt", '.'), 5);
	ASSERT_EQ_UINT(ft_lentc("hello", 'z'), 0);
	ASSERT_EQ_UINT(ft_lentc(NULL, '.'), 0);
}

TEST(string, lents_length_to_substring)
{
	ASSERT_EQ_UINT(ft_lents("hello world", "world"), 6);
	ASSERT_EQ_UINT(ft_lents("hello", "xyz"), 5);
}

TEST(string, strsncmp_prefix_match)
{
	ASSERT_EQ_INT(ft_strsncmp("hello", "hel", 0, 3), 0);
	ASSERT(ft_strsncmp("hello", "help", 0, 4) != 0);
}

/* ft_strzap only strips `pat` when it is a prefix of str, not anywhere in it. */
TEST(string, strzap_removes_matching_prefix)
{
	char *s = ft_strzap(strdup("hello world"), "hello ");

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "world");
	free(s);
}

TEST(string, strzap_no_match_returns_unchanged)
{
	char *s = ft_strzap(strdup("hello world"), "xyz");

	ASSERT_EQ_STR(s, "hello world");
	free(s);
}

TEST(string, substr_from_start_extracts_prefix)
{
	char *s = ft_substr(strdup("hello world"), 0, 5);

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "hello");
	free(s);
}

TEST(string, substr_nonzero_start_extracts_correct_slice)
{
	char *s = ft_substr(strdup("hello world"), 6, 5);

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "world");
	free(s);
}

TEST(string, substr_out_of_range_returns_input_unchanged)
{
	char *original = strdup("hi");
	char *s = ft_substr(original, 0, 99);

	ASSERT_EQ_STR(s, "hi");
	free(s);
}

static char to_upper_cb(unsigned int i, char c)
{
	(void)i;
	return (ft_toupper(c));
}

TEST(string, strmapi_transforms_each_char_with_index)
{
	char *s = ft_strmapi("abc", to_upper_cb);

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "ABC");
	free(s);
}

TEST(string, strmapi_null_returns_null)
{
	ASSERT_NULL(ft_strmapi(NULL, to_upper_cb));
}

TEST(string, strtrim_strips_only_leading_and_trailing_whitespace)
{
	char buf[32];
	char *r;

	strcpy(buf, "  a b  ");
	r = ft_strtrim(buf);
	ASSERT_EQ_PTR(r, buf);
	ASSERT_EQ_STR(buf, "a b");
}

TEST(string, strtrim_also_strips_tabs_and_newlines)
{
	char buf[32];

	strcpy(buf, "\ta\nb\t");
	ft_strtrim(buf);
	ASSERT_EQ_STR(buf, "a\nb");
}

TEST(string, strtrim_no_spaces_is_noop)
{
	char buf[16];

	strcpy(buf, "hello");
	ft_strtrim(buf);
	ASSERT_EQ_STR(buf, "hello");
}

TEST(string, strtrim_all_whitespace_becomes_empty)
{
	char buf[16];

	strcpy(buf, "   \t\n  ");
	ft_strtrim(buf);
	ASSERT_EQ_STR(buf, "");
}

TEST(string, strremove_deletes_every_matching_char)
{
	char *s = ft_strremove(strdup("banana"), 'a');

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "bnn");
	free(s);
}

TEST(string, strrdbls_collapses_consecutive_duplicates)
{
	char *s = ft_strrdbls(strdup("aaabbbccc"), 'b');

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "aaabccc");
	free(s);
}

TEST(string, strrep_replaces_substring)
{
	char *s = ft_strrep(strdup("hello world"), "world", "there");

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "hello there");
	free(s);
}

TEST(string, strrep_replaces_every_occurrence)
{
	char *s = ft_strrep(strdup("a-b-c-d"), "-", "_");

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "a_b_c_d");
	free(s);
}

TEST(string, strrep_pattern_absent_but_chars_overlap)
{
	char *s = ft_strrep(strdup("hello"), "xyz-not-there-e", "***");

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "hello");
	free(s);
}

TEST(string, strrep_pattern_genuinely_absent_no_overlap)
{
	char *s = ft_strrep(strdup("hello"), "xyz", "***");

	ASSERT_NOT_NULL(s);
	ASSERT_EQ_STR(s, "hello");
	free(s);
}

TEST(string, strsplit_splits_on_separator)
{
	char *words[8];
	char *src = strdup("one two three");
	char *r = ft_strsplit(src, words, " ");

	ASSERT_EQ_PTR(r, src);
	ASSERT_NOT_NULL(words[0]);
	ASSERT_MSG(!memcmp(words[0], "one", 3), "words[0] should start with "
		"\"one\", got \"%.3s\"", words[0]);
	free(src);
	free(words[0]);
	free(words[1]);
	free(words[2]);
}

TEST(string, strstr_finds_substring)
{
	const char *s = "hello world";

	ASSERT_EQ_PTR(ft_strstr(s, "world"), s + 6);
	ASSERT_EQ_PTR(ft_strstr(s, "hello"), s);
	ASSERT_NULL(ft_strstr(s, "xyz"));
}

TEST(string, strstr_empty_needle_returns_haystack)
{
	const char *s = "hello";

	ASSERT_EQ_PTR(ft_strstr(s, ""), s);
}

TEST(string, strstr_null_args_return_null)
{
	ASSERT_NULL(ft_strstr(NULL, "x"));
	ASSERT_NULL(ft_strstr("x", NULL));
}

TEST(string, strrchr_finds_last_occurrence)
{
	const char *s = "hello";

	ASSERT_EQ_PTR(ft_strrchr(s, 'l'), s + 3);
	ASSERT_EQ_PTR(ft_strrchr(s, 'h'), s);
	ASSERT_NULL(ft_strrchr(s, 'z'));
}

TEST(string, strrchr_finds_terminator)
{
	const char *s = "hello";

	ASSERT_EQ_PTR(ft_strrchr(s, '\0'), s + 5);
}

TEST(string, strcasecmp_ignores_case)
{
	ASSERT_EQ_INT(ft_strcasecmp("Hello", "HELLO"), 0);
	ASSERT_EQ_INT(ft_strcasecmp("abc", "abc"), 0);
	ASSERT(ft_strcasecmp("abc", "abd") < 0);
	ASSERT(ft_strcasecmp("ABD", "abc") > 0);
}

TEST(string, strncasecmp_ignores_case_within_length)
{
	ASSERT_EQ_INT(ft_strncasecmp("HELLOworld", "hello", 5), 0);
	ASSERT(ft_strncasecmp("HELLOa", "HELLOb", 6) != 0);
}

TEST(string, strupper_transforms_in_place)
{
	char buf[32];
	char *r;

	strcpy(buf, "Hello, World! 42");
	r = ft_strupper(buf);
	ASSERT_EQ_PTR(r, buf);
	ASSERT_EQ_STR(buf, "HELLO, WORLD! 42");
}

TEST(string, strlower_transforms_in_place)
{
	char buf[32];

	strcpy(buf, "Hello, World! 42");
	ft_strlower(buf);
	ASSERT_EQ_STR(buf, "hello, world! 42");
}

TEST(string, strupper_strlower_null_returns_null)
{
	ASSERT_NULL(ft_strupper(NULL));
	ASSERT_NULL(ft_strlower(NULL));
}
