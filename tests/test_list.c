/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

static void free_int(void *data)
{
	free(data);
}

static int list_compare_int(const void *a, const void *b)
{
	return (*(const int *)a - *(const int *)b);
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

TEST(list, delone_with_null_dispose_still_frees_node)
{
	t_list *node = ft_lstnew(NULL);

	ft_lstdelone(node, NULL);
}

TEST(list, delone_null_node_is_safe_noop)
{
	ft_lstdelone(NULL, free_int);
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

TEST(list, clear_on_null_lst_pointer_is_safe_noop)
{
	ft_lstclear(NULL, free_int);
}

TEST(list, remove_middle_node_relinks_neighbours)
{
	t_list *lst = NULL;
	t_list *a = make_int_node(1);
	t_list *b = make_int_node(2);
	t_list *c = make_int_node(3);

	ft_lstadd_back(&lst, a);
	ft_lstadd_back(&lst, b);
	ft_lstadd_back(&lst, c);
	ft_lstremove(&lst, b, free_int);
	ASSERT_EQ_PTR(lst, a);
	ASSERT_EQ_PTR(a->next, c);
	ASSERT_EQ_UINT(ft_lstsize(lst), 2);
	ft_lstclear(&lst, free_int);
}

TEST(list, remove_head_updates_lst_pointer)
{
	t_list *lst = NULL;
	t_list *a = make_int_node(1);
	t_list *b = make_int_node(2);

	ft_lstadd_back(&lst, a);
	ft_lstadd_back(&lst, b);
	ft_lstremove(&lst, a, free_int);
	ASSERT_EQ_PTR(lst, b);
	ft_lstclear(&lst, free_int);
}

TEST(list, remove_tail_updates_next_to_null)
{
	t_list *lst = NULL;
	t_list *a = make_int_node(1);
	t_list *b = make_int_node(2);

	ft_lstadd_back(&lst, a);
	ft_lstadd_back(&lst, b);
	ft_lstremove(&lst, b, free_int);
	ASSERT_EQ_PTR(lst, a);
	ASSERT_NULL(a->next);
	ft_lstclear(&lst, free_int);
}

TEST(list, remove_null_node_is_safe_noop)
{
	t_list *lst = NULL;

	ft_lstadd_back(&lst, make_int_node(1));
	ft_lstremove(&lst, NULL, free_int);
	ASSERT_EQ_UINT(ft_lstsize(lst), 1);
	ft_lstclear(&lst, free_int);
}

TEST(list, insert_before_middle_node)
{
	t_list *lst = NULL;
	t_list *a = make_int_node(1);
	t_list *c = make_int_node(3);
	t_list *b = make_int_node(2);

	ft_lstadd_back(&lst, a);
	ft_lstadd_back(&lst, c);
	ft_lstinsert_before(&lst, c, b);
	ASSERT_EQ_PTR(a->next, b);
	ASSERT_EQ_PTR(b->next, c);
	ASSERT_EQ_UINT(ft_lstsize(lst), 3);
	ft_lstclear(&lst, free_int);
}

TEST(list, insert_before_head_updates_lst_pointer)
{
	t_list *lst = NULL;
	t_list *b = make_int_node(2);
	t_list *a = make_int_node(1);

	ft_lstadd_back(&lst, b);
	ft_lstinsert_before(&lst, b, a);
	ASSERT_EQ_PTR(lst, a);
	ASSERT_EQ_PTR(a->next, b);
	ft_lstclear(&lst, free_int);
}

TEST(list, insert_after_middle_node)
{
	t_list *lst = NULL;
	t_list *a = make_int_node(1);
	t_list *c = make_int_node(3);
	t_list *b = make_int_node(2);

	ft_lstadd_back(&lst, a);
	ft_lstadd_back(&lst, c);
	ft_lstinsert_after(a, b);
	ASSERT_EQ_PTR(a->next, b);
	ASSERT_EQ_PTR(b->next, c);
	ft_lstclear(&lst, free_int);
}

TEST(list, insert_after_tail_becomes_new_tail)
{
	t_list *lst = NULL;
	t_list *a = make_int_node(1);
	t_list *b = make_int_node(2);

	ft_lstadd_back(&lst, a);
	ft_lstinsert_after(a, b);
	ASSERT_EQ_PTR(ft_lstlast(lst), b);
	ASSERT_NULL(b->next);
	ft_lstclear(&lst, free_int);
}

TEST(list, reverse_flips_order)
{
	t_list *lst = NULL;
	t_list *a = make_int_node(1);
	t_list *b = make_int_node(2);
	t_list *c = make_int_node(3);

	ft_lstadd_back(&lst, a);
	ft_lstadd_back(&lst, b);
	ft_lstadd_back(&lst, c);
	ft_lstreverse(&lst);
	ASSERT_EQ_PTR(lst, c);
	ASSERT_EQ_PTR(c->next, b);
	ASSERT_EQ_PTR(b->next, a);
	ASSERT_NULL(a->next);
	ft_lstclear(&lst, free_int);
}

TEST(list, reverse_empty_and_single_are_safe_noops)
{
	t_list *lst = NULL;
	t_list *only = make_int_node(1);

	ft_lstreverse(&lst);
	ASSERT_NULL(lst);
	ft_lstadd_back(&lst, only);
	ft_lstreverse(&lst);
	ASSERT_EQ_PTR(lst, only);
	ft_lstclear(&lst, free_int);
}

TEST(list, find_locates_matching_node)
{
	t_list *lst = NULL;
	t_list *target;
	int		key = 2;

	ft_lstadd_back(&lst, make_int_node(1));
	target = make_int_node(2);
	ft_lstadd_back(&lst, target);
	ft_lstadd_back(&lst, make_int_node(3));
	ASSERT_EQ_PTR(ft_lstfind(lst, &key, list_compare_int), target);
	ft_lstclear(&lst, free_int);
}

TEST(list, find_no_match_returns_null)
{
	t_list *lst = NULL;
	int		key = 99;

	ft_lstadd_back(&lst, make_int_node(1));
	ASSERT_NULL(ft_lstfind(lst, &key, list_compare_int));
	ASSERT_NULL(ft_lstfind(NULL, &key, list_compare_int));
	ft_lstclear(&lst, free_int);
}

TEST(list, at_returns_node_by_index)
{
	t_list *lst = NULL;
	t_list *a = make_int_node(1);
	t_list *b = make_int_node(2);
	t_list *c = make_int_node(3);

	ft_lstadd_back(&lst, a);
	ft_lstadd_back(&lst, b);
	ft_lstadd_back(&lst, c);
	ASSERT_EQ_PTR(ft_lstat(lst, 0), a);
	ASSERT_EQ_PTR(ft_lstat(lst, 1), b);
	ASSERT_EQ_PTR(ft_lstat(lst, 2), c);
	ASSERT_NULL(ft_lstat(lst, 3));
	ft_lstclear(&lst, free_int);
}
