/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_scanf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

static void with_stdin(const char *input, void (*action)(void))
{
    int pipefd[2];
    int saved_fd0;

    pipe(pipefd);
    write(pipefd[1], input, strlen(input));
    close(pipefd[1]);
    saved_fd0 = dup(0);
    dup2(pipefd[0], 0);
    close(pipefd[0]);
    action();
    dup2(saved_fd0, 0);
    close(saved_fd0);
}

TEST(sscanf, single_int)
{
    int n;
    int ret;

    ret = ft_sscanf("42", "%d", &n);
    ASSERT_EQ_INT(ret, 1);
    ASSERT_EQ_INT(n, 42);
}

TEST(sscanf, negative_int_with_leading_whitespace)
{
    int n;

    ASSERT_EQ_INT(ft_sscanf("   -123", "%d", &n), 1);
    ASSERT_EQ_INT(n, -123);
}

TEST(sscanf, int_min_and_max)
{
    int n;

    ASSERT_EQ_INT(ft_sscanf("2147483647", "%d", &n), 1);
    ASSERT_EQ_INT(n, 2147483647);
    ASSERT_EQ_INT(ft_sscanf("-2147483648", "%d", &n), 1);
    ASSERT_EQ_INT(n, -2147483648);
}

TEST(sscanf, multiple_conversions_in_order)
{
    int a;
    int b;
    int c;

    ASSERT_EQ_INT(ft_sscanf("1 2 3", "%d %d %d", &a, &b, &c), 3);
    ASSERT_EQ_INT(a, 1);
    ASSERT_EQ_INT(b, 2);
    ASSERT_EQ_INT(c, 3);
}

TEST(sscanf, literal_text_must_match)
{
    int n;

    ASSERT_EQ_INT(ft_sscanf("key=42", "key=%d", &n), 1);
    ASSERT_EQ_INT(n, 42);
    ASSERT_EQ_INT(ft_sscanf("nope=42", "key=%d", &n), 0);
}

/* %i auto-detects base from a prefix (hex/octal); %d always stays base 10. */
TEST(sscanf, i_auto_detects_base)
{
    int n;

    ASSERT_EQ_INT(ft_sscanf("0x1F", "%i", &n), 1);
    ASSERT_EQ_INT(n, 31);
    ASSERT_EQ_INT(ft_sscanf("017", "%i", &n), 1);
    ASSERT_EQ_INT(n, 15);
    ASSERT_EQ_INT(ft_sscanf("017", "%d", &n), 1);
    ASSERT_EQ_INT(n, 17);
}

TEST(sscanf, u_x_o_conversions)
{
    unsigned int u;

    ASSERT_EQ_INT(ft_sscanf("4294967295", "%u", &u), 1);
    ASSERT_EQ_UINT(u, 4294967295u);
    ASSERT_EQ_INT(ft_sscanf("ff", "%x", &u), 1);
    ASSERT_EQ_UINT(u, 255u);
    ASSERT_EQ_INT(ft_sscanf("0X1a", "%x", &u), 1);
    ASSERT_EQ_UINT(u, 26u);
    ASSERT_EQ_INT(ft_sscanf("17", "%o", &u), 1);
    ASSERT_EQ_UINT(u, 15u);
}

TEST(sscanf, length_modifiers)
{
    long        l;
    long long   ll;
    short       h;

    ASSERT_EQ_INT(ft_sscanf("123456789012", "%ld", &l), 1);
    ASSERT(l == 123456789012L);
    ASSERT_EQ_INT(ft_sscanf("123456789012345", "%lld", &ll), 1);
    ASSERT(ll == 123456789012345LL);
    ASSERT_EQ_INT(ft_sscanf("42", "%hd", &h), 1);
    ASSERT_EQ_INT(h, 42);
}

TEST(sscanf, s_stops_at_whitespace)
{
    char buf[32];

    ASSERT_EQ_INT(ft_sscanf("hello world", "%s", buf), 1);
    ASSERT_EQ_STR(buf, "hello");
}

TEST(sscanf, s_skips_leading_whitespace)
{
    char buf[32];

    ASSERT_EQ_INT(ft_sscanf("   hello", "%s", buf), 1);
    ASSERT_EQ_STR(buf, "hello");
}

TEST(sscanf, s_respects_width)
{
    char buf[32];

    ASSERT_EQ_INT(ft_sscanf("hello", "%3s", buf), 1);
    ASSERT_EQ_STR(buf, "hel");
}

/* %c does not skip leading whitespace and does not NUL-terminate. */
TEST(sscanf, c_does_not_skip_whitespace)
{
    char c;

    ASSERT_EQ_INT(ft_sscanf(" X", "%c", &c), 1);
    ASSERT_EQ_INT(c, ' ');
}

TEST(sscanf, c_multiple_reads_sequential_chars)
{
    char a;
    char b;

    ASSERT_EQ_INT(ft_sscanf("AB", "%c%c", &a, &b), 2);
    ASSERT_EQ_INT(a, 'A');
    ASSERT_EQ_INT(b, 'B');
}

TEST(sscanf, f_basic_and_exponent)
{
    float f;

    ASSERT_EQ_INT(ft_sscanf("3.14", "%f", &f), 1);
    ASSERT_EQ_DOUBLE(f, 3.14, 0.0001);
    ASSERT_EQ_INT(ft_sscanf("1e3", "%f", &f), 1);
    ASSERT_EQ_DOUBLE(f, 1000.0, 0.0001);
    ASSERT_EQ_INT(ft_sscanf("-2.5", "%f", &f), 1);
    ASSERT_EQ_DOUBLE(f, -2.5, 0.0001);
}

TEST(sscanf, f_into_double_with_l_modifier)
{
    double d;

    ASSERT_EQ_INT(ft_sscanf("3.14159", "%lf", &d), 1);
    ASSERT_EQ_DOUBLE(d, 3.14159, 0.00001);
}

/* The unmatched exponent suffix must be left unconsumed for the next conversion. */
TEST(sscanf, f_invalid_exponent_suffix_is_not_consumed)
{
    float   f;
    char    rest[16];

    ASSERT_EQ_INT(ft_sscanf("1e+x", "%f%s", &f, rest), 2);
    ASSERT_EQ_DOUBLE(f, 1.0, 0.0001);
    ASSERT_EQ_STR(rest, "e+x");
}

TEST(sscanf, suppressed_assignment_is_not_counted)
{
    int n;

    ASSERT_EQ_INT(ft_sscanf("42 7", "%*d %d", &n), 1);
    ASSERT_EQ_INT(n, 7);
}

TEST(sscanf, empty_input_returns_eof)
{
    int n;

    ASSERT_EQ_INT(ft_sscanf("", "%d", &n), -1);
}

TEST(sscanf, mismatched_input_returns_zero_not_eof)
{
    int n;

    ASSERT_EQ_INT(ft_sscanf("abc", "%d", &n), 0);
}

TEST(sscanf, partial_match_stops_and_reports_count_so_far)
{
    int a;
    int b;

    ASSERT_EQ_INT(ft_sscanf("1 abc", "%d %d", &a, &b), 1);
    ASSERT_EQ_INT(a, 1);
}

TEST(sscanf, null_arguments_do_not_crash)
{
    ASSERT_EQ_INT(ft_sscanf(NULL, NULL), 0);
}

static void action_scanf_int(void)
{
    int n;
    int ret;

    ret = ft_scanf("%d", &n);
    ASSERT_EQ_INT(ret, 1);
    ASSERT_EQ_INT(n, 42);
}

TEST(scanf, reads_int_from_stdin)
{
    with_stdin("42\n", action_scanf_int);
}

static void action_scanf_multi(void)
{
    int a;
    int b;
    char word[32];
    int ret;

    ret = ft_scanf("%d %s %d", &a, word, &b);
    ASSERT_EQ_INT(ret, 3);
    ASSERT_EQ_INT(a, 1);
    ASSERT_EQ_STR(word, "hello");
    ASSERT_EQ_INT(b, 2);
}

TEST(scanf, reads_multiple_conversions_from_stdin)
{
    with_stdin("1 hello 2", action_scanf_multi);
}

static void action_scanf_eof(void)
{
    int n;

    ASSERT_EQ_INT(ft_scanf("%d", &n), -1);
}

TEST(scanf, empty_stdin_returns_eof)
{
    with_stdin("", action_scanf_eof);
}
