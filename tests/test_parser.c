/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include "framework/test_framework.h"

/* --------------------------------------------------------- RAW ARG VIEW */

TEST(parser, nb_args_excludes_program_name)
{
	const char *argv[] = {"prog", "one", "two", "three", NULL};
	Parser *p = ft_parser(4, argv);

	ASSERT_NOT_NULL(p);
	ASSERT_EQ_UINT(p->nb_args, 3);
	ft_free_parser(&p);
}

TEST(parser, foreach_args_visits_real_args_only)
{
	const char *argv[] = {"prog", "one", "two", "three", NULL};
	Parser *p = ft_parser(4, argv);
	const char *seen[8];
	int count = 0;

	ASSERT_NOT_NULL(p);
	ForEachArgs(p)
	{
		ASSERT_NOT_NULL(arg->str);
		seen[count++] = arg->str;
	}
	ASSERT_EQ_INT(count, 3);
	ASSERT_EQ_STR(seen[0], "one");
	ASSERT_EQ_STR(seen[1], "two");
	ASSERT_EQ_STR(seen[2], "three");
	ft_free_parser(&p);
}

TEST(parser, foreach_args_index_matches_position)
{
	const char *argv[] = {"prog", "one", "two", "three", NULL};
	Parser *p = ft_parser(4, argv);
	size_t expected = 0;

	ForEachArgs(p)
	{
		ASSERT_EQ_UINT(arg->index, expected);
		++expected;
	}
	ASSERT_EQ_UINT(expected, 3u);
	ft_free_parser(&p);
}

TEST(parser, no_real_args_visits_nothing)
{
	const char *argv[] = {"prog", NULL};
	Parser *p = ft_parser(1, argv);
	int count = 0;

	ASSERT_NOT_NULL(p);
	ASSERT_EQ_UINT(p->nb_args, 0);
	ForEachArgs(p)
	{
		(void)arg;
		++count;
	}
	ASSERT_EQ_INT(count, 0);
	ft_free_parser(&p);
}

TEST(parser, free_parser_on_null_is_safe)
{
	Parser *p = NULL;

	ft_free_parser(&p);
}

/* ------------------------------------------------------ OPTION REGISTRY */

TEST(parser, add_option_basic_forms_succeed)
{
	const char *argv[] = {"prog", NULL};
	Parser *p = ft_parser(1, argv);

	ASSERT(parser_add_option(p, 'v', "verbose", PARSER_OPT_FLAG, "v", false));
	ASSERT(parser_add_option(p, '\0', "long-only", PARSER_OPT_FLAG, NULL, false));
	ASSERT(parser_add_option(p, 's', NULL, PARSER_OPT_FLAG, NULL, false));
	ft_free_parser(&p);
}

TEST(parser, add_option_without_short_or_long_fails)
{
	const char *argv[] = {"prog", NULL};
	Parser *p = ft_parser(1, argv);

	ASSERT(!parser_add_option(p, '\0', NULL, PARSER_OPT_FLAG, NULL, false));
	ft_free_parser(&p);
}

TEST(parser, add_option_duplicate_short_name_fails)
{
	const char *argv[] = {"prog", NULL};
	Parser *p = ft_parser(1, argv);

	ASSERT(parser_add_option(p, 'v', "verbose", PARSER_OPT_FLAG, NULL, false));
	ASSERT(!parser_add_option(p, 'v', "other", PARSER_OPT_FLAG, NULL, false));
	ft_free_parser(&p);
}

TEST(parser, add_option_duplicate_long_name_fails)
{
	const char *argv[] = {"prog", NULL};
	Parser *p = ft_parser(1, argv);

	ASSERT(parser_add_option(p, 'v', "verbose", PARSER_OPT_FLAG, NULL, false));
	ASSERT(!parser_add_option(p, 'x', "verbose", PARSER_OPT_FLAG, NULL, false));
	ft_free_parser(&p);
}

/* ---------------------------------------------------------------- FLAGS */

TEST(parser, parse_long_flag_sets_value)
{
	const char *argv[] = {"prog", "--verbose", NULL};
	Parser *p = ft_parser(2, argv);

	parser_add_option(p, 'v', "verbose", PARSER_OPT_FLAG, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT(parser_get_flag(p, "verbose"));
	ASSERT(parser_is_set(p, "verbose"));
	ft_free_parser(&p);
}

TEST(parser, parse_short_flag_sets_value)
{
	const char *argv[] = {"prog", "-v", NULL};
	Parser *p = ft_parser(2, argv);

	parser_add_option(p, 'v', "verbose", PARSER_OPT_FLAG, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT(parser_get_flag(p, "verbose"));
	ft_free_parser(&p);
}

TEST(parser, unset_flag_defaults_false)
{
	const char *argv[] = {"prog", NULL};
	Parser *p = ft_parser(1, argv);

	parser_add_option(p, 'v', "verbose", PARSER_OPT_FLAG, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT(!parser_get_flag(p, "verbose"));
	ASSERT(!parser_is_set(p, "verbose"));
	ft_free_parser(&p);
}

TEST(parser, parse_combined_short_flags)
{
	const char *argv[] = {"prog", "-abc", NULL};
	Parser *p = ft_parser(2, argv);

	parser_add_option(p, 'a', "aaa", PARSER_OPT_FLAG, NULL, false);
	parser_add_option(p, 'b', "bbb", PARSER_OPT_FLAG, NULL, false);
	parser_add_option(p, 'c', "ccc", PARSER_OPT_FLAG, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT(parser_get_flag(p, "aaa"));
	ASSERT(parser_get_flag(p, "bbb"));
	ASSERT(parser_get_flag(p, "ccc"));
	ft_free_parser(&p);
}

TEST(parser, flag_option_rejects_inline_value)
{
	const char *argv[] = {"prog", "--verbose=yes", NULL};
	Parser *p = ft_parser(2, argv);

	parser_add_option(p, 'v', "verbose", PARSER_OPT_FLAG, NULL, false);
	ASSERT(!parser_parse(p));
	ASSERT(parser_has_error(p));
	ft_free_parser(&p);
}

/* ------------------------------------------------------- STRING / INT */

TEST(parser, parse_long_option_equals_form)
{
	const char *argv[] = {"prog", "--name=Alice", NULL};
	Parser *p = ft_parser(2, argv);

	parser_add_option(p, 'n', "name", PARSER_OPT_STRING, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT_EQ_STR(parser_get_string(p, "name", "?"), "Alice");
	ft_free_parser(&p);
}

TEST(parser, parse_long_option_space_form)
{
	const char *argv[] = {"prog", "--name", "Alice", NULL};
	Parser *p = ft_parser(3, argv);

	parser_add_option(p, 'n', "name", PARSER_OPT_STRING, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT_EQ_STR(parser_get_string(p, "name", "?"), "Alice");
	ft_free_parser(&p);
}

TEST(parser, parse_short_option_glued_value)
{
	const char *argv[] = {"prog", "-nAlice", NULL};
	Parser *p = ft_parser(2, argv);

	parser_add_option(p, 'n', "name", PARSER_OPT_STRING, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT_EQ_STR(parser_get_string(p, "name", "?"), "Alice");
	ft_free_parser(&p);
}

TEST(parser, parse_short_option_space_value)
{
	const char *argv[] = {"prog", "-n", "Alice", NULL};
	Parser *p = ft_parser(3, argv);

	parser_add_option(p, 'n', "name", PARSER_OPT_STRING, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT_EQ_STR(parser_get_string(p, "name", "?"), "Alice");
	ft_free_parser(&p);
}

TEST(parser, parse_int_option_valid)
{
	const char *argv[] = {"prog", "--port=8080", NULL};
	Parser *p = ft_parser(2, argv);

	parser_add_option(p, 'p', "port", PARSER_OPT_INT, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT_EQ_INT(parser_get_int(p, "port", -1), 8080);
	ft_free_parser(&p);
}

TEST(parser, parse_int_option_negative_value)
{
	const char *argv[] = {"prog", "-p", "-42", NULL};
	Parser *p = ft_parser(3, argv);

	parser_add_option(p, 'p', "port", PARSER_OPT_INT, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT_EQ_INT(parser_get_int(p, "port", 0), -42);
	ft_free_parser(&p);
}

TEST(parser, get_string_default_when_not_set)
{
	const char *argv[] = {"prog", NULL};
	Parser *p = ft_parser(1, argv);

	parser_add_option(p, 'n', "name", PARSER_OPT_STRING, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT_EQ_STR(parser_get_string(p, "name", "default"), "default");
	ft_free_parser(&p);
}

TEST(parser, get_int_default_when_not_set)
{
	const char *argv[] = {"prog", NULL};
	Parser *p = ft_parser(1, argv);

	parser_add_option(p, 'p', "port", PARSER_OPT_INT, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT_EQ_INT(parser_get_int(p, "port", 99), 99);
	ft_free_parser(&p);
}

/* -------------------------------------------------------------- ERRORS */

TEST(parser, unknown_long_option_sets_error)
{
	const char *argv[] = {"prog", "--bogus", NULL};
	Parser *p = ft_parser(2, argv);

	ASSERT(!parser_parse(p));
	ASSERT(parser_has_error(p));
	ASSERT_NOT_NULL(strstr(parser_error_message(p), "bogus"));
	ft_free_parser(&p);
}

TEST(parser, unknown_short_option_sets_error)
{
	const char *argv[] = {"prog", "-z", NULL};
	Parser *p = ft_parser(2, argv);

	ASSERT(!parser_parse(p));
	ASSERT(parser_has_error(p));
	ft_free_parser(&p);
}

TEST(parser, missing_value_for_string_option_sets_error)
{
	const char *argv[] = {"prog", "--name", NULL};
	Parser *p = ft_parser(2, argv);

	parser_add_option(p, 'n', "name", PARSER_OPT_STRING, NULL, false);
	ASSERT(!parser_parse(p));
	ASSERT(parser_has_error(p));
	ft_free_parser(&p);
}

TEST(parser, invalid_integer_value_sets_error)
{
	const char *argv[] = {"prog", "--port=notanumber", NULL};
	Parser *p = ft_parser(2, argv);

	parser_add_option(p, 'p', "port", PARSER_OPT_INT, NULL, false);
	ASSERT(!parser_parse(p));
	ASSERT(parser_has_error(p));
	ft_free_parser(&p);
}

TEST(parser, missing_required_option_sets_error)
{
	const char *argv[] = {"prog", NULL};
	Parser *p = ft_parser(1, argv);

	parser_add_option(p, 'n', "name", PARSER_OPT_STRING, NULL, true);
	ASSERT(!parser_parse(p));
	ASSERT(parser_has_error(p));
	ASSERT_NOT_NULL(strstr(parser_error_message(p), "name"));
	ft_free_parser(&p);
}

TEST(parser, required_option_present_has_no_error)
{
	const char *argv[] = {"prog", "--name=x", NULL};
	Parser *p = ft_parser(2, argv);

	parser_add_option(p, 'n', "name", PARSER_OPT_STRING, NULL, true);
	ASSERT(parser_parse(p));
	ASSERT(!parser_has_error(p));
	ft_free_parser(&p);
}

/* ----------------------------------------------------------- POSITIONAL */

TEST(parser, positional_args_collected_in_order)
{
	const char *argv[] = {"prog", "-v", "one", "two", NULL};
	Parser *p = ft_parser(4, argv);

	parser_add_option(p, 'v', "verbose", PARSER_OPT_FLAG, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT_EQ_UINT(parser_positional_count(p), 2u);
	ASSERT_EQ_STR(parser_get_positional(p, 0), "one");
	ASSERT_EQ_STR(parser_get_positional(p, 1), "two");
	ASSERT_NULL(parser_get_positional(p, 2));
	ft_free_parser(&p);
}

TEST(parser, double_dash_stops_option_parsing)
{
	const char *argv[] = {"prog", "one", "--", "-v", "--name=x", NULL};
	Parser *p = ft_parser(5, argv);

	parser_add_option(p, 'v', "verbose", PARSER_OPT_FLAG, NULL, false);
	ASSERT(parser_parse(p));
	ASSERT(!parser_get_flag(p, "verbose"));
	ASSERT_EQ_UINT(parser_positional_count(p), 3u);
	ASSERT_EQ_STR(parser_get_positional(p, 0), "one");
	ASSERT_EQ_STR(parser_get_positional(p, 1), "-v");
	ASSERT_EQ_STR(parser_get_positional(p, 2), "--name=x");
	ft_free_parser(&p);
}

/* ------------------------------------------------------------- USAGE */

TEST(parser, usage_string_lists_every_option)
{
	const char *argv[] = {"prog", NULL};
	Parser *p = ft_parser(1, argv);
	char *usage;

	parser_add_option(p, 'v', "verbose", PARSER_OPT_FLAG,
		"Verbose output", false);
	parser_add_option(p, 'n', "name", PARSER_OPT_STRING, "Your name", true);
	usage = parser_usage_string(p, "myprog");
	ASSERT_NOT_NULL(usage);
	ASSERT_NOT_NULL(strstr(usage, "myprog"));
	ASSERT_NOT_NULL(strstr(usage, "-v, --verbose"));
	ASSERT_NOT_NULL(strstr(usage, "Verbose output"));
	ASSERT_NOT_NULL(strstr(usage, "-n, --name"));
	ASSERT_NOT_NULL(strstr(usage, "(required)"));
	free(usage);
	ft_free_parser(&p);
}
