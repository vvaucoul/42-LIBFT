/* ************************************************************************** */
/*   test_memory.c - srcs/memory/ *.c                                         */
/*                                                                            */
/*   Several functions here (ft_memchr, ft_memcmp, ft_memscmp, ft_memshr)    */
/*   share a `while (--len)` idiom that (a) never examines the last byte of  */
/*   the range and (b) underflows `size_t` to SIZE_MAX when len == 0,       */
/*   turning a single call into a near-infinite out-of-bounds scan. Those    */
/*   len==0 cases are deliberately their own TEST() so the fork+alarm        */
/*   isolation in the framework reports a clean TIMEOUT/CRASH line instead   */
/*   of hanging the whole suite.                                             */
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

/* Naive forward-only copy loop: doesn't detect dest > src overlap the way a
** real memmove must, so a right-shift within the same buffer corrupts data
** it hasn't read yet instead of preserving it. */
TEST(memory, memmove_overlap_forward_shift_known_bug)
{
	char buf[9] = "ABCDEFGH";

	ft_memmove(buf + 2, buf, 5);
	ASSERT_MSG(!memcmp(buf, "ABABCDEH", 8),
		"ft_memmove(buf+2, buf, 5) on \"ABCDEFGH\": expected \"ABABCDEH\" "
		"(correct memmove semantics), got \"%.8s\"", buf);
}

TEST(memory, memmove_no_overlap_is_correct)
{
	char buf[11] = "HelloWorld";

	ft_memmove(buf + 5, buf, 5);
	ASSERT_EQ_MEM(buf, "HelloHello", 10);
}

TEST(memory, memmove_null_src_returns_null)
{
	char dst[4];

	ASSERT_NULL(ft_memmove(dst, NULL, 4));
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

/* while (--len) never compares index (len - 1): if the ONLY difference is
** in the last byte of the range, ft_memcmp misses it and reports "equal". */
TEST(memory, memcmp_difference_only_in_last_byte_known_bug)
{
	ASSERT_MSG(ft_memcmp("abcX", "abcY", 4) != 0,
		"ft_memcmp(\"abcX\", \"abcY\", 4) should differ (last byte X vs Y) "
		"but the buggy `while (--len)` loop never inspects index len-1");
}

TEST(memory, memcmp_zero_len_known_bug_isolated)
{
	/* len == 0 underflows to SIZE_MAX inside `while (--len)`: this either
	** segfaults on an out-of-bounds read or times out. Either outcome is
	** reported as a clean failure by the runner instead of hanging it. */
	ft_memcmp("a", "b", 0);
}

TEST(memory, memchr_finds_middle_byte)
{
	char buf[6] = "hello";
	void *p = ft_memchr(buf, 'l', 5);

	ASSERT_EQ_PTR(p, buf + 2);
}

/* Same last-byte blind spot as memcmp: searching for the value that only
** occurs at index len-1 never gets checked. */
TEST(memory, memchr_last_byte_known_bug)
{
	char buf[6] = "hello";

	ASSERT_MSG(ft_memchr(buf, 'o', 5) != NULL,
		"ft_memchr(\"hello\", 'o', 5) should find 'o' at index 4, but the "
		"buggy `while (--len)` loop never inspects the last byte");
}

TEST(memory, memchr_not_found_returns_null)
{
	char buf[6] = "hello";

	ASSERT_NULL(ft_memchr(buf, 'z', 5));
}

TEST(memory, memchr_zero_len_known_bug_isolated)
{
	char buf[4] = "abc";

	ft_memchr(buf, 'a', 0);
}

TEST(memory, memscmp_skips_start_offset)
{
	/* ft_memscmp advances BOTH buffers by `start` (not just the first one),
	** so the comparison buffer needs its own start-byte padding too. */
	char buf[9] = "XXXhello";
	char cmp[9] = "YYYhello";

	ASSERT_EQ_INT(ft_memscmp(buf, cmp, 8, 3), 0);
}

TEST(memory, memscmp_zero_effective_len_known_bug_isolated)
{
	/* start == len drives the remaining length to 0 before the buggy
	** `while (--len)` loop, underflowing the same way as memcmp/memchr. */
	ft_memscmp("abc", "abc", 3, 3);
}

TEST(memory, memshr_finds_subsequence_at_start)
{
	char buf[6] = "hello";

	ASSERT_NOT_NULL(ft_memshr(buf, "he", 5, 2));
}

TEST(memory, memshr_zero_len_known_bug_isolated)
{
	char buf[4] = "abc";

	ft_memshr(buf, "a", 0, 1);
}

/* ft_memlower/ft_memupper only advance their write cursor *inside* the
** if-branch that performs a conversion - once a byte that needs no
** conversion is hit, the cursor stops moving and every remaining iteration
** re-inspects that same byte, silently skipping the rest of the buffer. */
TEST(memory, memlower_stalls_after_first_no_op_byte_known_bug)
{
	char buf[4] = "AbC";

	ft_memlower(buf, 3);
	ASSERT_MSG(!memcmp(buf, "abc", 3),
		"ft_memlower(\"AbC\", 3): expected \"abc\", got \"%.3s\" (cursor "
		"stalls at the first already-lowercase byte)", buf);
}

TEST(memory, memupper_stalls_after_first_no_op_byte_known_bug)
{
	char buf[4] = "aBc";

	ft_memupper(buf, 3);
	ASSERT_MSG(!memcmp(buf, "ABC", 3),
		"ft_memupper(\"aBc\", 3): expected \"ABC\", got \"%.3s\" (cursor "
		"stalls at the first already-uppercase byte)", buf);
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
	/* Oversized backing buffer: the shift loop inside ft_memcrm reads one
	** byte past the requested length on its last iteration, so we give it
	** real bytes to read there instead of relying on UB. */
	char buf[16] = "banana__slack__";

	ft_memcrm(buf, 'a', 6);
	ASSERT_MSG(!memcmp(buf, "bnn", 3),
		"ft_memcrm(\"banana\", 'a', 6): expected compacted prefix \"bnn\", "
		"got \"%.3s\"", buf);
}

TEST(memory, memsrm_removes_any_char_in_set)
{
	char buf[16] = "a1b2c3__slack__";

	ft_memsrm(buf, "123", 6);
	ASSERT_MSG(!memcmp(buf, "abc", 3),
		"ft_memsrm(\"a1b2c3\", \"123\", 6): expected compacted prefix "
		"\"abc\", got \"%.3s\"", buf);
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
