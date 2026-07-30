/* ************************************************************************** */
/*   test_parser.c - srcs/parser/parser.c                                    */
/*                                                                            */
/*   ft_parser() has an off-by-one: it builds nb_args+1 nodes (the extra one */
/*   holding argv[argc] == NULL, per the C standard's argv NULL sentinel).   */
/*   The ForEachArgs() macro in turn stops one node early (its condition is  */
/*   `arg->next != NULL`, checked before running the body for the LAST      */
/*   node). The two bugs happen to cancel out: ForEachArgs visits exactly   */
/*   the real arguments and never reaches the bogus trailing NULL node.     */
/*   That's what's asserted below - not "no bugs here", just "these two     */
/*   specific bugs currently offset each other".                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include "framework/test_framework.h"

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
