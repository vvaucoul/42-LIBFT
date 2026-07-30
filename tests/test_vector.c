/* ************************************************************************** */
/*   test_vector.c - srcs/classes/vector.c                                   */
/*                                                                            */
/*   vector_resize() only updates vector->size on the SHRINK path; the grow */
/*   path leaves it stale. vector_push_back() compensates with a manual     */
/*   `++vector->size` after resizing, so push_back works correctly, but     */
/*   vector_insert()/vector_pop_back()/vector_assign() (which don't do that */
/*   manual bump, or which underflow size_t first) inherit real bugs -      */
/*   see the known_bug tests below. Each Vector* is independently           */
/*   heap-allocated (no shared global state to worry about between tests).  */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

TEST(vector, new_is_empty)
{
	Vector *v = vector_new(sizeof(int), 4);

	ASSERT_NOT_NULL(v);
	ASSERT_EQ_UINT(vector_size(v), 0);
	ASSERT(vector_empty(v));
	vector_delete(v);
}

TEST(vector, push_back_grows_size_and_stores_value)
{
	int a = 1;
	int b = 2;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	ASSERT_EQ_UINT(vector_size(v), 2);
	ASSERT_EQ_PTR(vector_at(v, 0), &a);
	ASSERT_EQ_PTR(vector_at(v, 1), &b);
	vector_delete(v);
}

TEST(vector, at_out_of_bounds_returns_null)
{
	Vector *v = vector_new(sizeof(void *), 0);

	ASSERT_NULL(vector_at(v, 0));
	ASSERT_NULL(vector_at(v, 99));
	vector_delete(v);
}

TEST(vector, front_and_back_after_pushes)
{
	int a = 1;
	int b = 2;
	int c = 3;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	vector_push_back(v, &c);
	ASSERT_EQ_PTR(vector_front(v), &a);
	ASSERT_EQ_PTR(vector_back(v), &c);
	vector_delete(v);
}

TEST(vector, erase_shifts_remaining_elements)
{
	int a = 1;
	int b = 2;
	int c = 3;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	vector_push_back(v, &c);
	vector_erase(v, 1);
	ASSERT_EQ_UINT(vector_size(v), 2);
	ASSERT_EQ_PTR(vector_at(v, 0), &a);
	ASSERT_EQ_PTR(vector_at(v, 1), &c);
	vector_delete(v);
}

TEST(vector, clear_empties_vector)
{
	int a = 1;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_clear(v);
	ASSERT_EQ_UINT(vector_size(v), 0);
	ASSERT(vector_empty(v));
	vector_delete(v);
}

TEST(vector, swap_exchanges_two_slots)
{
	int a = 1;
	int b = 2;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	vector_swap(v, 0, 1);
	ASSERT_EQ_PTR(vector_at(v, 0), &b);
	ASSERT_EQ_PTR(vector_at(v, 1), &a);
	vector_delete(v);
}

/* vector_insert()'s grow-resize leaves vector->size stale (see file header
** note), and vector_insert never manually bumps it the way push_back
** does - so after a middle insert, vector_size() doesn't reflect the new
** element at all. */
TEST(vector, insert_updates_size_known_bug)
{
	int a = 1;
	int b = 2;
	int c = 3;
	Vector *v = vector_new(sizeof(void *), 0);

	vector_push_back(v, &a);
	vector_push_back(v, &b);
	vector_insert(v, &c, 1);
	ASSERT_MSG(vector_size(v) == 3,
		"vector_insert should grow the vector to size 3, got %zu",
		vector_size(v));
	vector_delete(v);
}

/* vector_pop_back() on an empty vector computes `vector_size(v) - 1`,
** underflowing size_t to SIZE_MAX, which then drives a "grow to SIZE_MAX"
** reallocation - a massive out-of-bounds write / heap corruption. Isolated
** so the crash only costs this one test line. */
TEST(vector, pop_back_on_empty_known_bug_isolated)
{
	Vector *v = vector_new(sizeof(void *), 0);

	vector_pop_back(v);
	vector_delete(v);
}
