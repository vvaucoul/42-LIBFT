/* ************************************************************************** */
/*                                                                            */
/*   test_framework.h - tiny self-registering, fork-isolated unit test kit   */
/*                                                                            */
/*   Each TEST(suite, name) { ... } block auto-registers itself (constructor */
/*   attribute) - no manual list of test files to maintain. test_run_all()   */
/*   forks a fresh child per test with a hard timeout, so a segfault or an   */
/*   infinite loop in the function under test only kills that one test.     */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <string.h>

typedef void (*t_test_fn)(void);

void test_register(const char *suite, const char *name, t_test_fn fn);
int  test_run_all(int verbose);

/* Prints the failure and terminates the current test (forked child) only. */
void t_fail(const char *file, int line, const char *fmt, ...)
	__attribute__((noreturn, format(printf, 3, 4)));

/* Redirects fd 1 for the duration of `action`, returns the captured bytes
** as a malloc'd, NUL-terminated buffer (caller must free it). Meant to be
** called from inside a test to check what ft_putstr/ft_printf/... wrote. */
char *test_capture_fd1(void (*action)(void));

/* ------------------------------------------------------------------ TEST */

#define TEST(suite, name) \
	static void test_##suite##_##name(void); \
	__attribute__((constructor)) \
	static void test_register_##suite##_##name(void) \
	{ \
		test_register(#suite, #name, test_##suite##_##name); \
	} \
	static void test_##suite##_##name(void)

/* --------------------------------------------------------------- ASSERTS */

#define ASSERT(cond) \
	do { \
		if (!(cond)) \
			t_fail(__FILE__, __LINE__, "ASSERT(%s) failed", #cond); \
	} while (0)

#define ASSERT_MSG(cond, ...) \
	do { \
		if (!(cond)) \
			t_fail(__FILE__, __LINE__, __VA_ARGS__); \
	} while (0)

#define ASSERT_EQ_INT(actual, expected) \
	do { \
		long long _a = (long long)(actual); \
		long long _e = (long long)(expected); \
		if (_a != _e) \
			t_fail(__FILE__, __LINE__, "%s: expected %lld, got %lld", \
				#actual, _e, _a); \
	} while (0)

#define ASSERT_EQ_UINT(actual, expected) \
	do { \
		unsigned long long _a = (unsigned long long)(actual); \
		unsigned long long _e = (unsigned long long)(expected); \
		if (_a != _e) \
			t_fail(__FILE__, __LINE__, "%s: expected %llu, got %llu", \
				#actual, _e, _a); \
	} while (0)

#define ASSERT_EQ_DOUBLE(actual, expected, eps) \
	do { \
		double _a = (double)(actual); \
		double _e = (double)(expected); \
		double _d = _a - _e; \
		if (_d < 0) \
			_d = -_d; \
		if (_d > (eps)) \
			t_fail(__FILE__, __LINE__, "%s: expected %g, got %g", \
				#actual, _e, _a); \
	} while (0)

#define ASSERT_NULL(ptr) \
	do { \
		if ((ptr) != NULL) \
			t_fail(__FILE__, __LINE__, "%s: expected NULL, got %p", \
				#ptr, (void *)(ptr)); \
	} while (0)

#define ASSERT_NOT_NULL(ptr) \
	do { \
		if ((ptr) == NULL) \
			t_fail(__FILE__, __LINE__, "%s: expected non-NULL, got NULL", \
				#ptr); \
	} while (0)

#define ASSERT_EQ_STR(actual, expected) \
	do { \
		const char *_a = (actual); \
		const char *_e = (expected); \
		if (_a == NULL || _e == NULL) \
		{ \
			if (_a != _e) \
				t_fail(__FILE__, __LINE__, \
					"%s: expected %s, got %s", #actual, \
					_e ? _e : "(null)", _a ? _a : "(null)"); \
		} \
		else if (strcmp(_a, _e) != 0) \
			t_fail(__FILE__, __LINE__, "%s: expected \"%s\", got \"%s\"", \
				#actual, _e, _a); \
	} while (0)

#define ASSERT_EQ_MEM(actual, expected, n) \
	do { \
		if (memcmp((actual), (expected), (n)) != 0) \
			t_fail(__FILE__, __LINE__, "%s: memory block differs from %s " \
				"over %zu bytes", #actual, #expected, (size_t)(n)); \
	} while (0)

#define ASSERT_EQ_PTR(actual, expected) \
	do { \
		if ((const void *)(actual) != (const void *)(expected)) \
			t_fail(__FILE__, __LINE__, "%s: expected pointer %p, got %p", \
				#actual, (const void *)(expected), (const void *)(actual)); \
	} while (0)

#define FAIL(...) t_fail(__FILE__, __LINE__, __VA_ARGS__)

#endif
