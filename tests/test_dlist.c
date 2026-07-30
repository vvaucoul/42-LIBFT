/* ************************************************************************** */
/*   test_dlist.c - srcs/dlinked_list/ *.c (t_dlist, doubly linked)           */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

static void free_int(void *data)
{
	free(data);
}

static int g_iter_sum;

static void add_to_sum(void *data)
{
	g_iter_sum += *(int *)data;
}

static t_dlist *make_int_node(int value)
{
	int *data = malloc(sizeof(int));

	*data = value;
	return (ft_dlstnew(data));
}

TEST(dlist, new_node_holds_data)
{
	int value = 42;
	t_dlist *node = ft_dlstnew(&value);

	ASSERT_NOT_NULL(node);
	ASSERT_EQ_PTR(node->data, &value);
	ASSERT_NULL(node->next);
	ASSERT_NULL(node->prev);
	free(node);
}

TEST(dlist, add_back_links_prev_and_next)
{
	t_dlist *lst = NULL;
	t_dlist *a = make_int_node(1);
	t_dlist *b = make_int_node(2);

	ft_dlstadd_back(&lst, a);
	ASSERT_EQ_PTR(lst, a);
	ft_dlstadd_back(&lst, b);
	ASSERT_EQ_PTR(lst->next, b);
	ASSERT_EQ_PTR(b->prev, a);
	ft_dlstclear(&lst, free_int);
	ASSERT_NULL(lst);
}

TEST(dlist, add_front_links_prev_and_next)
{
	t_dlist *lst = NULL;
	t_dlist *a = make_int_node(1);
	t_dlist *b = make_int_node(2);

	ft_dlstadd_front(&lst, a);
	ft_dlstadd_front(&lst, b);
	ASSERT_EQ_PTR(lst, b);
	ASSERT_EQ_PTR(lst->next, a);
	ASSERT_EQ_PTR(a->prev, b);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, size_counts_nodes)
{
	t_dlist *lst = NULL;

	ASSERT_EQ_UINT(ft_dlstsize(lst), 0);
	ft_dlstadd_back(&lst, make_int_node(1));
	ft_dlstadd_back(&lst, make_int_node(2));
	ft_dlstadd_back(&lst, make_int_node(3));
	ASSERT_EQ_UINT(ft_dlstsize(lst), 3);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, last_returns_tail)
{
	t_dlist *lst = NULL;
	t_dlist *c;

	ASSERT_NULL(ft_dlstlast(NULL));
	ft_dlstadd_back(&lst, make_int_node(1));
	c = make_int_node(2);
	ft_dlstadd_back(&lst, c);
	ASSERT_EQ_PTR(ft_dlstlast(lst), c);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, iter_visits_every_node)
{
	t_dlist *lst = NULL;

	g_iter_sum = 0;
	ft_dlstadd_back(&lst, make_int_node(10));
	ft_dlstadd_back(&lst, make_int_node(20));
	ft_dlstadd_back(&lst, make_int_node(30));
	ft_dlstiter(lst, add_to_sum);
	ASSERT_EQ_INT(g_iter_sum, 60);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, delone_frees_and_nulls_the_slot)
{
	t_dlist *node = make_int_node(7);

	ft_dlstdelone(&node, free_int);
	ASSERT_NULL(node);
}

TEST(dlist, clear_empties_and_nulls_head)
{
	t_dlist *lst = NULL;

	ft_dlstadd_back(&lst, make_int_node(1));
	ft_dlstadd_back(&lst, make_int_node(2));
	ft_dlstclear(&lst, free_int);
	ASSERT_NULL(lst);
}
