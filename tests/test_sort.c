/* ************************************************************************** */
/*   test_sort.c - srcs/sort/ *.c                                             */
/*                                                                            */
/*   ft_qsort(array, low, high, size, compare) takes INCLUSIVE bounds - for  */
/*   N elements callers must pass low=0, high=N-1 (matches the header        */
/*   exactly; there is no bounds checking, passing high=N reads/writes one   */
/*   element past the end). Its internal `partition()` reseeds `srand(time  */
/*   (NULL))` on every call, so pivot selection is not reproducible between */
/*   runs - tests only assert the final array is sorted, never anything     */
/*   about comparison counts or intermediate order.                         */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(sort, qsort_sorts_ascending)
{
	int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6, 0};

	ft_qsort(arr, 0, 9, sizeof(int), compare_int);
	for (int i = 0; i < 10; ++i)
		ASSERT_EQ_INT(arr[i], i);
}

TEST(sort, qsort_single_element_is_noop)
{
	int arr[] = {42};

	ft_qsort(arr, 0, 0, sizeof(int), compare_int);
	ASSERT_EQ_INT(arr[0], 42);
}

TEST(sort, bsort_sorts_ascending)
{
	int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6, 0};

	ft_bsort(arr, 10, sizeof(int), compare_int);
	for (int i = 0; i < 10; ++i)
		ASSERT_EQ_INT(arr[i], i);
}

TEST(sort, bsort_empty_and_single_are_safe_noops)
{
	int arr[] = {42};

	ft_bsort(arr, 0, sizeof(int), compare_int);
	ft_bsort(arr, 1, sizeof(int), compare_int);
	ASSERT_EQ_INT(arr[0], 42);
}

TEST(sort, isort_sorts_ascending)
{
	int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6, 0};

	ft_isort(arr, 10, sizeof(int), compare_int);
	for (int i = 0; i < 10; ++i)
		ASSERT_EQ_INT(arr[i], i);
}

TEST(sort, isort_empty_and_single_are_safe_noops)
{
	int arr[] = {42};

	ft_isort(arr, 0, sizeof(int), compare_int);
	ft_isort(arr, 1, sizeof(int), compare_int);
	ASSERT_EQ_INT(arr[0], 42);
}

TEST(sort, sswap_exchanges_elements)
{
	int a = 1;
	int b = 2;

	ft_sswap(&a, &b, sizeof(int));
	ASSERT_EQ_INT(a, 2);
	ASSERT_EQ_INT(b, 1);
}

TEST(sort, is_sorted_true_and_false)
{
	int sorted[] = {1, 2, 3, 4, 5};
	int unsorted[] = {1, 3, 2, 4, 5};

	ASSERT_EQ_INT(is_sorted(sorted, 5, sizeof(int), compare_int), 1);
	ASSERT_EQ_INT(is_sorted(unsorted, 5, sizeof(int), compare_int), 0);
}

TEST(sort, is_sorted_equal_adjacent_elements_counts_as_sorted)
{
	int arr[] = {1, 2, 2, 3};

	ASSERT_EQ_INT(is_sorted(arr, 4, sizeof(int), compare_int), 1);
}

TEST(sort, is_sorted_empty_and_single_are_vacuously_true)
{
	int arr[] = {42};

	ASSERT_EQ_INT(is_sorted(arr, 0, sizeof(int), compare_int), 1);
	ASSERT_EQ_INT(is_sorted(arr, 1, sizeof(int), compare_int), 1);
}

TEST(sort, compare_int_basic_ordering)
{
	int a = 1;
	int b = 2;

	ASSERT(compare_int(&a, &b) < 0);
	ASSERT(compare_int(&b, &a) > 0);
	ASSERT_EQ_INT(compare_int(&a, &a), 0);
}

TEST(sort, compare_char_basic_ordering)
{
	char a = 'a';
	char b = 'b';

	ASSERT(compare_char(&a, &b) < 0);
	ASSERT(compare_char(&b, &a) > 0);
}

TEST(sort, compare_str_basic_ordering)
{
	const char *a = "abc";
	const char *b = "abd";

	ASSERT(compare_str(&a, &b) < 0);
}

/* compare_double/compare_float return type is `int`, so the floating-point
** difference gets truncated toward zero on the implicit conversion. Any
** two values whose real difference has magnitude < 1.0 compare as equal. */
TEST(sort, compare_double_sub_one_magnitude_diff_known_bug)
{
	double a = 0.9;
	double b = 0.3;

	ASSERT_MSG(compare_double(&a, &b) > 0,
		"compare_double(0.9, 0.3) should be > 0 (0.9 > 0.3), got %d "
		"(the 0.6 difference truncates to 0 through the int return type)",
		compare_double(&a, &b));
}

TEST(sort, compare_float_sub_one_magnitude_diff_known_bug)
{
	float a = 0.9f;
	float b = 0.3f;

	ASSERT_MSG(compare_float(&a, &b) > 0,
		"compare_float(0.9f, 0.3f) should be > 0, got %d",
		compare_float(&a, &b));
}

/* compare_long/compare_ulong/compare_llong/compare_ullong have the exact
** same truncate-to-int bug: a difference outside INT_MIN..INT_MAX silently
** wraps when converted to the `int` return value, and can even flip the
** sign - so the comparator can report a > b as a < b. */
TEST(sort, compare_long_overflow_flips_sign_known_bug)
{
	long a = 3000000000L;
	long b = 0L;

	ASSERT_MSG(compare_long(&a, &b) > 0,
		"compare_long(3000000000, 0) should be > 0, got %d (the ~3e9 "
		"difference overflows the int return type and can flip sign)",
		compare_long(&a, &b));
}
