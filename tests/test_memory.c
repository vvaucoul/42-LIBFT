/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(memory, memset_fills_buffer)
{
	char buf[8];

	ft_memset(buf, 'x', 8);
	ASSERT_EQ_MEM(buf, "xxxxxxxx", 8);
}

TEST(memory, memset_zero_len_noop)
{
	char buf[4] = {'a', 'b', 'c', 'd'};

	ft_memset(buf, 'x', 0);
	ASSERT_EQ_MEM(buf, "abcd", 4);
}

TEST(memory, bzero_clears_buffer)
{
	char buf[8] = "ABCDEFG";

	ft_bzero(buf, 8);
	ASSERT_EQ_MEM(buf, "\0\0\0\0\0\0\0\0", 8);
}

TEST(memory, memcpy_copies_bytes)
{
	char src[6] = "Hello";
	char dst[6] = {0};

	ft_memcpy(dst, src, 6);
	ASSERT_EQ_MEM(dst, "Hello", 6);
}

TEST(memory, memcpy_null_returns_null)
{
	char buf[4] = {0};

	ASSERT_NULL(ft_memcpy(NULL, buf, 4));
	ASSERT_NULL(ft_memcpy(buf, NULL, 4));
}

TEST(memory, memmove_overlap_forward_shift_is_correct)
{
	char buf[9] = "ABCDEFGH";

	ft_memmove(buf + 2, buf, 5);
	ASSERT_EQ_MEM(buf, "ABABCDEH", 8);
}

TEST(memory, memmove_overlap_backward_shift_is_correct)
{
	char buf[9] = "ABCDEFGH";

	ft_memmove(buf, buf + 2, 5);
	ASSERT_EQ_MEM(buf, "CDEFGFGH", 8);
}

TEST(memory, memmove_no_overlap_is_correct)
{
	char buf[11] = "HelloWorld";

	ft_memmove(buf + 5, buf, 5);
	ASSERT_EQ_MEM(buf, "HelloHello", 10);
}

TEST(memory, memmove_null_returns_null)
{
	char dst[4];

	ASSERT_NULL(ft_memmove(dst, NULL, 4));
	ASSERT_NULL(ft_memmove(NULL, dst, 4));
}

TEST(memory, memcmp_equal_buffers)
{
	ASSERT_EQ_INT(ft_memcmp("abcd", "abcd", 4), 0);
}

TEST(memory, memcmp_difference_before_last_byte)
{
	ASSERT(ft_memcmp("abcd", "abXd", 4) != 0);
	ASSERT(ft_memcmp("Xbcd", "abcd", 4) != 0);
}

TEST(memory, memcmp_difference_in_last_byte_is_detected)
{
	ASSERT(ft_memcmp("abcX", "abcY", 4) != 0);
}

TEST(memory, memcmp_zero_len_returns_zero)
{
	ASSERT_EQ_INT(ft_memcmp("a", "b", 0), 0);
}

TEST(memory, memchr_finds_middle_byte)
{
	char buf[6] = "hello";
	void *p = ft_memchr(buf, 'l', 5);

	ASSERT_EQ_PTR(p, buf + 2);
}

TEST(memory, memchr_finds_last_byte)
{
	char buf[6] = "hello";

	ASSERT_EQ_PTR(ft_memchr(buf, 'o', 5), buf + 4);
}

TEST(memory, memchr_not_found_returns_null)
{
	char buf[6] = "hello";

	ASSERT_NULL(ft_memchr(buf, 'z', 5));
}

TEST(memory, memchr_zero_len_returns_null)
{
	char buf[4] = "abc";

	ASSERT_NULL(ft_memchr(buf, 'a', 0));
}

TEST(memory, memrchr_finds_last_matching_occurrence)
{
	char buf[6] = "hello";

	ASSERT_EQ_PTR(ft_memrchr(buf, 'l', 5), buf + 3);
}

TEST(memory, memrchr_finds_only_occurrence_at_start)
{
	char buf[6] = "hello";

	ASSERT_EQ_PTR(ft_memrchr(buf, 'h', 5), buf);
}

TEST(memory, memrchr_not_found_returns_null)
{
	char buf[6] = "hello";

	ASSERT_NULL(ft_memrchr(buf, 'z', 5));
}

TEST(memory, memrchr_zero_len_returns_null)
{
	char buf[4] = "abc";

	ASSERT_NULL(ft_memrchr(buf, 'a', 0));
}

TEST(memory, memscmp_skips_start_offset)
{
	/* ft_memscmp advances both buffers by `start`, so cmp needs its own padding. */
	char buf[9] = "XXXhello";
	char cmp[9] = "YYYhello";

	ASSERT_EQ_INT(ft_memscmp(buf, cmp, 8, 3), 0);
}

TEST(memory, memscmp_zero_effective_len_returns_zero)
{
	ASSERT_EQ_INT(ft_memscmp("abc", "abc", 3, 3), 0);
}

TEST(memory, memscmp_start_greater_than_len_returns_zero)
{
	ASSERT_EQ_INT(ft_memscmp("abc", "abc", 2, 5), 0);
}

TEST(memory, memshr_finds_subsequence_at_start)
{
	char buf[6] = "hello";

	ASSERT_EQ_PTR(ft_memshr(buf, "he", 5, 2), buf);
}

TEST(memory, memshr_finds_subsequence_at_end)
{
	char buf[6] = "hello";

	ASSERT_EQ_PTR(ft_memshr(buf, "lo", 5, 2), buf + 3);
}

TEST(memory, memshr_not_found_returns_null)
{
	char buf[6] = "hello";

	ASSERT_NULL(ft_memshr(buf, "xy", 5, 2));
}

TEST(memory, memshr_needle_longer_than_haystack_returns_null)
{
	char buf[4] = "abc";

	ASSERT_NULL(ft_memshr(buf, "a", 0, 1));
	ASSERT_NULL(ft_memshr(buf, "abcd", 3, 4));
}

TEST(memory, memlower_converts_every_uppercase_byte)
{
	char buf[4] = "AbC";

	ft_memlower(buf, 3);
	ASSERT_EQ_MEM(buf, "abc", 3);
}

TEST(memory, memupper_converts_every_lowercase_byte)
{
	char buf[4] = "aBc";

	ft_memupper(buf, 3);
	ASSERT_EQ_MEM(buf, "ABC", 3);
}

TEST(memory, memlower_all_uppercase_works)
{
	char buf[6] = "HELLO";

	ft_memlower(buf, 5);
	ASSERT_EQ_MEM(buf, "hello", 5);
}

TEST(memory, memupper_all_lowercase_works)
{
	char buf[6] = "hello";

	ft_memupper(buf, 5);
	ASSERT_EQ_MEM(buf, "HELLO", 5);
}

TEST(memory, memcrm_removes_all_occurrences)
{
	char buf[6] = "banana";

	ft_memcrm(buf, 'a', 6);
	ASSERT_EQ_MEM(buf, "bnn", 3);
}

TEST(memory, memcrm_no_match_leaves_buffer_unchanged)
{
	char buf[4] = "abc";

	ft_memcrm(buf, 'z', 3);
	ASSERT_EQ_MEM(buf, "abc", 3);
}

TEST(memory, memsrm_removes_any_char_in_set)
{
	char buf[6] = "a1b2c3";

	ft_memsrm(buf, "123", 6);
	ASSERT_EQ_MEM(buf, "abc", 3);
}

TEST(memory, memalloc_copies_into_new_buffer)
{
	void *dst = NULL;
	char src[6] = "Hello";

	ft_memalloc(&dst, src, sizeof(char), 5);
	ASSERT_NOT_NULL(dst);
	ASSERT_EQ_MEM(dst, "Hello", 5);
	free(dst);
}

TEST(memory, memalloc_null_ref_returns_null)
{
	void *dst = (void *)1;

	ASSERT_NULL(ft_memalloc(&dst, NULL, sizeof(char), 5));
}

TEST(memory, swap_ints)
{
	int a = 1;
	int b = 2;

	ft_swap(&a, &b);
	ASSERT_EQ_INT(a, 2);
	ASSERT_EQ_INT(b, 1);
}

TEST(memory, vswap_pointers)
{
	int x = 1;
	int y = 2;
	void *a = &x;
	void *b = &y;

	ft_vswap(&a, &b);
	ASSERT_EQ_PTR(a, &y);
	ASSERT_EQ_PTR(b, &x);
}
