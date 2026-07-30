/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

static const char   *g_fmt;
static int          g_int_arg;
static const char   *g_str_arg;
static char         g_char_arg;
static int          g_ret;

static void action_d(void)
{
    g_ret = ft_printf(g_fmt, g_int_arg);
}

static void action_s(void)
{
    g_ret = ft_printf(g_fmt, g_str_arg);
}

static void action_cd(void)
{
    g_ret = ft_printf(g_fmt, g_char_arg, g_int_arg);
}

TEST(printf, d_and_i_print_normally)
{
    char *out;

    g_fmt = "%d";
    g_int_arg = 42;
    out = test_capture_fd1(action_d);
    ASSERT_EQ_STR(out, "42");
    free(out);

    g_fmt = "%i";
    g_int_arg = -7;
    out = test_capture_fd1(action_d);
    ASSERT_EQ_STR(out, "-7");
    free(out);
}

TEST(printf, s_prints_string)
{
    char *out;

    g_fmt = "%s";
    g_str_arg = "hello";
    out = test_capture_fd1(action_s);
    ASSERT_EQ_STR(out, "hello");
    free(out);
}

TEST(printf, s_null_prints_parenthesized_null)
{
    char *out;

    g_fmt = "%s";
    g_str_arg = NULL;
    out = test_capture_fd1(action_s);
    ASSERT_EQ_STR(out, "(null)");
    free(out);
}

TEST(printf, return_value_is_bytes_written)
{
    g_fmt = "%s";
    g_str_arg = "some non-empty output";
    free(test_capture_fd1(action_s));
    ASSERT_EQ_INT(g_ret, (int)strlen("some non-empty output"));
}

TEST(printf, unsupported_conversion_prints_literally_no_desync)
{
    char *out;

    g_fmt = "%c%d";
    g_char_arg = 'A';
    g_int_arg = 99;
    out = test_capture_fd1(action_cd);
    ASSERT_EQ_STR(out, "A99");
    free(out);
}

static void action_bogus(void)
{
    g_ret = ft_printf("%q%d", 42);
}

TEST(printf, truly_unknown_conversion_is_literal_and_safe)
{
    char *out;

    out = test_capture_fd1(action_bogus);
    ASSERT_EQ_STR(out, "%q42");
    free(out);
}

static void action_literal_percent(void)
{
    g_ret = ft_printf("100%%");
}

TEST(printf, percent_percent_prints_literal_percent)
{
    char *out;

    out = test_capture_fd1(action_literal_percent);
    ASSERT_EQ_STR(out, "100%");
    free(out);
}

static void action_trailing_percent(void)
{
    g_ret = ft_printf("abc%");
}

TEST(printf, trailing_percent_is_printed_literally)
{
    char *out;

    out = test_capture_fd1(action_trailing_percent);
    ASSERT_EQ_STR(out, "abc%");
    free(out);
}

static void action_int_min(void)
{
    g_ret = ft_printf("%d", -2147483648);
}

TEST(printf, d_int_min_prints_correctly)
{
    char *out;

    out = test_capture_fd1(action_int_min);
    ASSERT_EQ_STR(out, "-2147483648");
    free(out);
}

TEST(printf, unsigned_and_hex_and_octal)
{
    char buf[64];

    ft_sprintf(buf, "%u", 4294967295u);
    ASSERT_EQ_STR(buf, "4294967295");
    ft_sprintf(buf, "%x", 255);
    ASSERT_EQ_STR(buf, "ff");
    ft_sprintf(buf, "%X", 255);
    ASSERT_EQ_STR(buf, "FF");
    ft_sprintf(buf, "%o", 8);
    ASSERT_EQ_STR(buf, "10");
}

TEST(printf, flags_width_precision)
{
    char buf[64];

    ft_sprintf(buf, "%5d", 42);
    ASSERT_EQ_STR(buf, "   42");
    ft_sprintf(buf, "%-5d|", 42);
    ASSERT_EQ_STR(buf, "42   |");
    ft_sprintf(buf, "%05d", 42);
    ASSERT_EQ_STR(buf, "00042");
    ft_sprintf(buf, "%+d", 42);
    ASSERT_EQ_STR(buf, "+42");
    ft_sprintf(buf, "% d", 42);
    ASSERT_EQ_STR(buf, " 42");
    ft_sprintf(buf, "%.5d", 42);
    ASSERT_EQ_STR(buf, "00042");
    ft_sprintf(buf, "%#x", 255);
    ASSERT_EQ_STR(buf, "0xff");
    ft_sprintf(buf, "%#o", 8);
    ASSERT_EQ_STR(buf, "010");
}

TEST(printf, precision_zero_value_zero_prints_nothing)
{
    char buf[64];

    ft_sprintf(buf, "[%.0d]", 0);
    ASSERT_EQ_STR(buf, "[]");
}

TEST(printf, star_width_and_precision)
{
    char buf[64];

    ft_sprintf(buf, "%*d", 8, 42);
    ASSERT_EQ_STR(buf, "      42");
    ft_sprintf(buf, "%.*f", 2, 3.14159);
    ASSERT_EQ_STR(buf, "3.14");
}

TEST(printf, length_modifiers_truncate_correctly)
{
    char buf[64];

    ft_sprintf(buf, "%hhd", 200);
    ASSERT_EQ_STR(buf, "-56");
    ft_sprintf(buf, "%ld", 123456789012L);
    ASSERT_EQ_STR(buf, "123456789012");
    ft_sprintf(buf, "%lld", 123456789012345LL);
    ASSERT_EQ_STR(buf, "123456789012345");
}

TEST(printf, char_and_pointer)
{
    char buf[64];
    int  x;

    ft_sprintf(buf, "%c", 'Z');
    ASSERT_EQ_STR(buf, "Z");
    ft_sprintf(buf, "%5c", 'Z');
    ASSERT_EQ_STR(buf, "    Z");
    ft_sprintf(buf, "%p", (void *)NULL);
    ASSERT_EQ_STR(buf, "(nil)");
    ft_sprintf(buf, "%p", (void *)&x);
    ASSERT_NOT_NULL(strstr(buf, "0x"));
}

TEST(printf, float_basic_and_precision)
{
    char buf[64];

    ft_sprintf(buf, "%f", 3.14159);
    ASSERT_EQ_STR(buf, "3.141590");
    ft_sprintf(buf, "%.2f", 3.14159);
    ASSERT_EQ_STR(buf, "3.14");
    ft_sprintf(buf, "%8.2f", 3.14159);
    ASSERT_EQ_STR(buf, "    3.14");
    ft_sprintf(buf, "%-8.2f|", 3.14159);
    ASSERT_EQ_STR(buf, "3.14    |");
    ft_sprintf(buf, "%08.2f", 3.14159);
    ASSERT_EQ_STR(buf, "00003.14");
    ft_sprintf(buf, "%f", -3.14159);
    ASSERT_EQ_STR(buf, "-3.141590");
    ft_sprintf(buf, "%.0f", 3.7);
    ASSERT_EQ_STR(buf, "4");
}

TEST(printf, dprintf_writes_to_arbitrary_fd)
{
    int     pipefd[2];
    char    buf[32];
    ssize_t n;
    int     ret;

    ASSERT(pipe(pipefd) == 0);
    ret = ft_dprintf(pipefd[1], "count=%d", 42);
    close(pipefd[1]);
    n = read(pipefd[0], buf, sizeof(buf) - 1);
    close(pipefd[0]);
    ASSERT(n >= 0);
    buf[n] = '\0';
    ASSERT_EQ_STR(buf, "count=42");
    ASSERT_EQ_INT(ret, 8);
}

/* Mirrors the real (unbounded, unsafe) sprintf() contract. */
TEST(printf, sprintf_writes_to_buffer)
{
    char buf[64];
    int  ret;

    ret = ft_sprintf(buf, "%s is %d", "answer", 42);
    ASSERT_EQ_STR(buf, "answer is 42");
    ASSERT_EQ_INT(ret, 12);
}

TEST(printf, snprintf_truncates_but_reports_full_length)
{
    char buf[8];
    int  ret;

    ret = ft_snprintf(buf, sizeof(buf), "%s", "this is way too long");
    ASSERT_EQ_STR(buf, "this is");
    ASSERT_EQ_INT(ret, (int)strlen("this is way too long"));
}

TEST(printf, snprintf_zero_size_writes_nothing)
{
    char buf[4] = "XXX";

    ft_snprintf(buf, 0, "%d", 42);
    ASSERT_EQ_STR(buf, "XXX");
}

static int wrap_vprintf(const char *fmt, ...)
{
    va_list args;
    int     ret;

    va_start(args, fmt);
    ret = ft_vprintf(fmt, args);
    va_end(args);
    return (ret);
}

static void action_vprintf(void)
{
    g_ret = wrap_vprintf("%d-%s", 7, "ok");
}

TEST(printf, vprintf_variant_works)
{
    char *out;

    out = test_capture_fd1(action_vprintf);
    ASSERT_EQ_STR(out, "7-ok");
    free(out);
    ASSERT_EQ_INT(g_ret, 4);
}
