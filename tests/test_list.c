/* ************************************************************************** */
/*   test_list.c - srcs/linked_list/ *.c (t_list, singly linked)              */
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

static t_list *make_int_node(int value)
{
	int *data = malloc(sizeof(int));

	*data = value;
	return (ft_lstnew(data));
}

TEST(list, new_node_holds_data)
{
	int value = 42;
	t_list *node = ft_lstnew(&value);

	ASSERT_NOT_NULL(node);
	ASSERT_EQ_PTR(node->data, &value);
	ASSERT_NULL(node->next);
	free(node);
}

TEST(list, add_back_on_empty_and_non_empty)
{
	t_list *lst = NULL;
	t_list *a = make_int_node(1);
	t_list *b = make_int_node(2);

	ft_lstadd_back(&lst, a);
	ASSERT_EQ_PTR(lst, a);
	ft_lstadd_back(&lst, b);
	ASSERT_EQ_PTR(lst->next, b);
	ASSERT_NULL(b->next);
	ft_lstclear(&lst, free_int);
	ASSERT_NULL(lst);
}

TEST(list, add_front_on_empty_and_non_empty)
{
	t_list *lst = NULL;
	t_list *a = make_int_node(1);
	t_list *b = make_int_node(2);

	ft_lstadd_front(&lst, a);
	ASSERT_EQ_PTR(lst, a);
	ft_lstadd_front(&lst, b);
	ASSERT_EQ_PTR(lst, b);
	ASSERT_EQ_PTR(lst->next, a);
	ft_lstclear(&lst, free_int);
}

TEST(list, size_counts_nodes)
{
	t_list *lst = NULL;

	ASSERT_EQ_UINT(ft_lstsize(lst), 0);
	ft_lstadd_back(&lst, make_int_node(1));
	ft_lstadd_back(&lst, make_int_node(2));
	ft_lstadd_back(&lst, make_int_node(3));
	ASSERT_EQ_UINT(ft_lstsize(lst), 3);
	ft_lstclear(&lst, free_int);
}

TEST(list, last_returns_tail)
{
	t_list *lst = NULL;
	t_list *c;

	ASSERT_NULL(ft_lstlast(NULL));
	ft_lstadd_back(&lst, make_int_node(1));
	ft_lstadd_back(&lst, make_int_node(2));
	c = make_int_node(3);
	ft_lstadd_back(&lst, c);
	ASSERT_EQ_PTR(ft_lstlast(lst), c);
	ft_lstclear(&lst, free_int);
}

TEST(list, iter_visits_every_node_in_order)
{
	t_list *lst = NULL;

	g_iter_sum = 0;
	ft_lstadd_back(&lst, make_int_node(1));
	ft_lstadd_back(&lst, make_int_node(2));
	ft_lstadd_back(&lst, make_int_node(3));
	ft_lstiter(lst, add_to_sum);
	ASSERT_EQ_INT(g_iter_sum, 6);
	ft_lstclear(&lst, free_int);
}

TEST(list, delone_frees_single_node)
{
	t_list *node = make_int_node(7);

	ft_lstdelone(node, free_int);
}

TEST(list, clear_empties_and_nulls_head)
{
	t_list *lst = NULL;

	ft_lstadd_back(&lst, make_int_node(1));
	ft_lstadd_back(&lst, make_int_node(2));
	ft_lstclear(&lst, free_int);
	ASSERT_NULL(lst);
	ASSERT_EQ_UINT(ft_lstsize(lst), 0);
}
