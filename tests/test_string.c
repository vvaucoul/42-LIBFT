/* ************************************************************************** */
/*   test_string.c - srcs/string/ft_strings.c                                */
/*                                                                            */
/*   Several functions here `free()` the pointer they are handed (ft_strzap, */
/*   ft_substr, ft_strremove, ft_strrdbls) or mutate it in place             */
/*   (ft_strtrim) - those tests use libc strdup()/malloc() to build a real,  */
/*   independently freeable heap buffer rather than a string literal.       */
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

/* ft_strcpy's very first line is `if (str) return (NULL);` - inverted from
** the obviously-intended `if (!str)`. Any call with a real (non-NULL)
** source string returns NULL immediately instead of copying it. */
TEST(string, strcpy_always_null_on_real_input_known_bug)
{
	char dest[16];

	ASSERT_MSG(ft_strcpy(dest, "hi") != NULL,
		"ft_strcpy(dest, \"hi\") should copy and return dest, but the "
		"inverted `if (str) return NULL;` guard makes it always return "
		"NULL for a non-NULL source");
}

/* ft_strdup allocates ft_calloc(sizeof(char), ft_strlen(str)) - exactly
** strlen(str) bytes, with no "+1" for the NUL terminator - so the copy
** fills the entire buffer and is never actually NUL-terminated. */
TEST(string, strdup_missing_null_terminator_known_bug_isolated)
{
	char *dup = ft_strdup("hello");

	ASSERT_NOT_NULL(dup);
	ASSERT_MSG(!memcmp(dup, "hello", 5),
		"ft_strdup(\"hello\") should at least copy the 5 bytes correctly");
	/* Reading `dup` as a NUL-terminated string past this point (strlen,
	** printf %s, strcmp...) is technically an out-of-bounds read - the
	** allocation is exactly 5 bytes long. Not done here on purpose. */
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

/* ft_strzap only strips `pat` when it is a PREFIX of str (via
** ft_strsncmp), not "anywhere in the string" despite the generic name. */
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

/* The copy loop is `for (i = start; str[i] && i < len; ++i)` - the upper
** bound compares the absolute index `i` against `len` instead of against
** `start + len`. Whenever `start >= len` (an extremely common case - any
** substring that doesn't start at/near index 0), the loop condition is
** false on its very first check and nothing is ever copied. */
TEST(string, substr_nonzero_start_known_bug)
{
	char *s = ft_substr(strdup("hello world"), 6, 5);

	ASSERT_NOT_NULL(s);
	ASSERT_MSG(!strcmp(s, "world"),
		"ft_substr(\"hello world\", 6, 5) should extract \"world\", got "
		"\"%s\" (the loop bound `i < len` should be `i < start + len`)", s);
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

/* ft_strtrim removes EVERY ' ' character it finds by scanning left to
** right and memmove-ing the rest of the string over it - leading,
** trailing, AND internal spaces are all stripped. This is a much broader
** operation than a typical "trim" (leading/trailing only). It also only
** recognizes ' ' (see ft_isspace), not \t \n etc. Mutates in place and
** returns the same pointer, so it needs a writable buffer, not a literal. */
TEST(string, strtrim_removes_every_space_not_just_edges_known_bug)
{
	char buf[32];
	char *r;

	strcpy(buf, "  a b  ");
	r = ft_strtrim(buf);
	ASSERT_EQ_PTR(r, buf);
	ASSERT_MSG(!strcmp(buf, "ab"),
		"ft_strtrim(\"  a b  \"): expected \"ab\" (it strips every space, "
		"not just the leading/trailing ones), got \"%s\"", buf);
}

TEST(string, strtrim_no_spaces_is_noop)
{
	char buf[16];

	strcpy(buf, "hello");
	ft_strtrim(buf);
	ASSERT_EQ_STR(buf, "hello");
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

/* ft_strrep bails out early with NULL only via ft_scof(src, pat), which
** checks character-level overlap between src and pat, NOT whether pat
** occurs as a substring of src - a much weaker (and different) test than
** what the early-return is presumably meant to guard. This makes the
** "no match" return value inconsistent: sometimes an unchanged copy,
** sometimes NULL, depending on incidental shared characters. */
TEST(string, strrep_pattern_absent_but_chars_overlap_known_bug)
{
	char *s = ft_strrep(strdup("hello"), "xyz-not-there-e", "***");

	ASSERT_NOT_NULL(s);
	ASSERT_MSG(!strcmp(s, "hello"),
		"ft_strrep with a non-matching pattern should return the string "
		"unchanged, got \"%s\"", s ? s : "(null)");
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
