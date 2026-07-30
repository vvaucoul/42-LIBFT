/* ************************************************************************** */
/*   test_array.c - srcs/array/ *.c                                          */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(array, acof_found_and_missing)
{
	const char *arr[] = {"foo", "bar", "baz", NULL};

	ASSERT(ft_acof(arr, "bar") == true);
	ASSERT(ft_acof(arr, "qux") == false);
	ASSERT(ft_acof(NULL, "bar") == false);
	ASSERT(ft_acof(arr, NULL) == false);
}

TEST(array, alen_counts_entries)
{
	const char *arr[] = {"a", "b", "c", NULL};
	const char *empty[] = {NULL};

	ASSERT_EQ_UINT(ft_alen(arr), 3);
	ASSERT_EQ_UINT(ft_alen(empty), 0);
	ASSERT_EQ_UINT(ft_alen(NULL), 0);
}

/* ft_asize's inner-loop cursor `j` is declared OUTSIDE the row loop and is
** never reset back to 0 between rows: each row's scan resumes indexing
** from wherever the previous (possibly longer) row left off. With rows of
** non-decreasing length this never walks past a row's own NUL byte, so the
** result matches the intended "(nb_rows + 1) * (longest_row + 1)" formula
** - this case is safe and deterministic. */
TEST(array, asize_uses_longest_row_and_count)
{
	const char *arr[] = {"a", "bb", "ccc", NULL};

	ASSERT_EQ_UINT(ft_asize(arr), (3 + 1) * (3 + 1));
	ASSERT_EQ_UINT(ft_asize(NULL), 0);
}

/* Same non-reset cursor bug, isolated on its own: once a row is SHORTER
** than the running cursor, the inner loop reads past that row's NUL
** terminator into whatever memory follows the string literal/buffer,
** silently continuing to scan out-of-bounds. The exact byte count read
** depends on adjacent memory layout, so we only assert it doesn't crash -
** not a specific value. */
TEST(array, asize_cursor_not_reset_between_rows_known_bug)
{
	const char *arr[] = {"abc", "a", NULL};

	(void)ft_asize(arr);
}

TEST(array, acol_returns_longest_row_len_plus_one)
{
	const char *arr[] = {"a", "bb", "ccc", NULL};

	ASSERT_EQ_UINT(ft_acol(arr), 3 + 1);
}

TEST(array, split_basic)
{
	char **words = ft_split("a,bb,ccc", ',');

	ASSERT_NOT_NULL(words);
	ASSERT_EQ_STR(words[0], "a");
	ASSERT_EQ_STR(words[1], "bb");
	ASSERT_EQ_STR(words[2], "ccc");
	ASSERT_NULL(words[3]);
}

TEST(array, split_consecutive_and_edge_delimiters)
{
	char **words = ft_split(",a,,b,", ',');

	ASSERT_NOT_NULL(words);
	ASSERT_EQ_STR(words[0], "");
	ASSERT_EQ_STR(words[1], "a");
	ASSERT_EQ_STR(words[2], "");
	ASSERT_EQ_STR(words[3], "b");
	ASSERT_EQ_STR(words[4], "");
	ASSERT_NULL(words[5]);
}

TEST(array, split_no_delimiter_present)
{
	char **words = ft_split("hello", ',');

	ASSERT_NOT_NULL(words);
	ASSERT_EQ_STR(words[0], "hello");
	ASSERT_NULL(words[1]);
}

TEST(array, split_null_returns_null)
{
	ASSERT_NULL(ft_split(NULL, ','));
}

/* ft_acpy copies element i via ft_strcpy(new_array[i], arr[i]) where
** new_array[i] starts NULL. ft_strcpy has an inverted guard
** (`if (str) return NULL;`) so it returns NULL whenever the source string
** is non-NULL - every single copy silently fails and ft_acpy ends up
** producing an array of NULL entries instead of copied strings. */
TEST(array, acpy_broken_by_strcpy_bug_known_bug)
{
	const char *arr[] = {"foo", "bar", NULL};
	char **copy = ft_acpy(arr);

	ASSERT_NOT_NULL(copy);
	ASSERT_MSG(copy[0] != NULL && !strcmp(copy[0], "foo"),
		"ft_acpy(arr)[0]: expected \"foo\", got %s (ft_strcpy always "
		"returns NULL on a non-NULL source string)",
		copy[0] ? copy[0] : "(null)");
}

TEST(array, sort_array_ints)
{
	int arr[] = {5, 3, 4, 1, 2};

	sort_array(arr, 5, sizeof(int), compare_int);
	for (int i = 0; i < 5; ++i)
		ASSERT_EQ_INT(arr[i], i + 1);
}

TEST(array, reverse_array_ints)
{
	int arr[] = {1, 2, 3, 4, 5};

	ft_reverse_array(arr, 5, sizeof(int));
	ASSERT_EQ_INT(arr[0], 5);
	ASSERT_EQ_INT(arr[1], 4);
	ASSERT_EQ_INT(arr[2], 3);
	ASSERT_EQ_INT(arr[3], 2);
	ASSERT_EQ_INT(arr[4], 1);
}

TEST(array, min_in_array_small_values)
{
	int arr[] = {5, 3, 9, 1, 7};

	/* value fits in a byte, so the return-truncation bug below doesn't
	** manifest here - a genuinely correct case. */
	ASSERT_EQ_INT(ft_min_in_array(arr, 5, sizeof(int)), 1);
}

/* ft_max_in_array/ft_min_in_array correctly locate the extreme element via
** ft_memcmp over the whole elem_size, but then `return *max;` dereferences
** only the FIRST BYTE of that element through a char*. For any value that
** doesn't fit in a single (signed) byte, the returned "max" is garbage. */
TEST(array, max_in_array_truncates_to_one_byte_known_bug)
{
	int arr[] = {300, 5, 1};

	ASSERT_MSG(ft_max_in_array(arr, 3, sizeof(int)) == 300,
		"ft_max_in_array({300,5,1}): expected 300, got %d (only the low "
		"byte of the winning element is returned)",
		ft_max_in_array(arr, 3, sizeof(int)));
}
