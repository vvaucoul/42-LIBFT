/* ************************************************************************** */
/*                                                                            */
/*   main.c - test runner entry point                                        */
/*                                                                            */
/*   All actual test cases live in tests/test_*.c and self-register via the  */
/*   TEST(suite, name) { ... } macro from tests/framework/test_framework.h - */
/*   nothing to list/wire up here. Add a new tests/test_whatever.c file and  */
/*   it is picked up automatically by the Makefile (`find tests -name       */
/*   '*.c'`) and by the constructor-based auto-registration at startup.     */
/*                                                                            */
/* ************************************************************************** */

#include "framework/test_framework.h"

int	main(int argc, char **argv)
{
	int	verbose;

	verbose = (argc > 1 && (!strcmp(argv[1], "-v")
			|| !strcmp(argv[1], "--verbose")));
	printf("\033[1mlibft test suite\033[0m\n");
	return (test_run_all(verbose));
}
