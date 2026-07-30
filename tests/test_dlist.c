/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dlist.c                                       :+:      :+:    :+:   */
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

static int dlist_compare_int(const void *a, const void *b)
{
	return (*(const int *)a - *(const int *)b);
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

TEST(dlist, remove_middle_node_relinks_neighbours)
{
	t_dlist *lst = NULL;
	t_dlist *a = make_int_node(1);
	t_dlist *b = make_int_node(2);
	t_dlist *c = make_int_node(3);

	ft_dlstadd_back(&lst, a);
	ft_dlstadd_back(&lst, b);
	ft_dlstadd_back(&lst, c);
	ft_dlstremove(&lst, b, free_int);
	ASSERT_EQ_PTR(lst, a);
	ASSERT_EQ_PTR(a->next, c);
	ASSERT_EQ_PTR(c->prev, a);
	ASSERT_EQ_UINT(ft_dlstsize(lst), 2);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, remove_head_updates_lst_pointer)
{
	t_dlist *lst = NULL;
	t_dlist *a = make_int_node(1);
	t_dlist *b = make_int_node(2);

	ft_dlstadd_back(&lst, a);
	ft_dlstadd_back(&lst, b);
	ft_dlstremove(&lst, a, free_int);
	ASSERT_EQ_PTR(lst, b);
	ASSERT_NULL(b->prev);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, remove_tail_updates_next_to_null)
{
	t_dlist *lst = NULL;
	t_dlist *a = make_int_node(1);
	t_dlist *b = make_int_node(2);

	ft_dlstadd_back(&lst, a);
	ft_dlstadd_back(&lst, b);
	ft_dlstremove(&lst, b, free_int);
	ASSERT_EQ_PTR(lst, a);
	ASSERT_NULL(a->next);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, remove_null_node_is_safe_noop)
{
	t_dlist *lst = NULL;

	ft_dlstadd_back(&lst, make_int_node(1));
	ft_dlstremove(&lst, NULL, free_int);
	ASSERT_EQ_UINT(ft_dlstsize(lst), 1);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, insert_before_middle_node)
{
	t_dlist *lst = NULL;
	t_dlist *a = make_int_node(1);
	t_dlist *c = make_int_node(3);
	t_dlist *b = make_int_node(2);

	ft_dlstadd_back(&lst, a);
	ft_dlstadd_back(&lst, c);
	ft_dlstinsert_before(&lst, c, b);
	ASSERT_EQ_PTR(a->next, b);
	ASSERT_EQ_PTR(b->prev, a);
	ASSERT_EQ_PTR(b->next, c);
	ASSERT_EQ_PTR(c->prev, b);
	ASSERT_EQ_UINT(ft_dlstsize(lst), 3);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, insert_before_head_updates_lst_pointer)
{
	t_dlist *lst = NULL;
	t_dlist *b = make_int_node(2);
	t_dlist *a = make_int_node(1);

	ft_dlstadd_back(&lst, b);
	ft_dlstinsert_before(&lst, b, a);
	ASSERT_EQ_PTR(lst, a);
	ASSERT_NULL(a->prev);
	ASSERT_EQ_PTR(a->next, b);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, insert_after_middle_node)
{
	t_dlist *lst = NULL;
	t_dlist *a = make_int_node(1);
	t_dlist *c = make_int_node(3);
	t_dlist *b = make_int_node(2);

	ft_dlstadd_back(&lst, a);
	ft_dlstadd_back(&lst, c);
	ft_dlstinsert_after(a, b);
	ASSERT_EQ_PTR(a->next, b);
	ASSERT_EQ_PTR(b->prev, a);
	ASSERT_EQ_PTR(b->next, c);
	ASSERT_EQ_PTR(c->prev, b);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, insert_after_tail_becomes_new_tail)
{
	t_dlist *lst = NULL;
	t_dlist *a = make_int_node(1);
	t_dlist *b = make_int_node(2);

	ft_dlstadd_back(&lst, a);
	ft_dlstinsert_after(a, b);
	ASSERT_EQ_PTR(ft_dlstlast(lst), b);
	ASSERT_NULL(b->next);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, reverse_flips_order_and_links)
{
	t_dlist *lst = NULL;
	t_dlist *a = make_int_node(1);
	t_dlist *b = make_int_node(2);
	t_dlist *c = make_int_node(3);

	ft_dlstadd_back(&lst, a);
	ft_dlstadd_back(&lst, b);
	ft_dlstadd_back(&lst, c);
	ft_dlstreverse(&lst);
	ASSERT_EQ_PTR(lst, c);
	ASSERT_NULL(c->prev);
	ASSERT_EQ_PTR(c->next, b);
	ASSERT_EQ_PTR(b->prev, c);
	ASSERT_EQ_PTR(b->next, a);
	ASSERT_EQ_PTR(a->prev, b);
	ASSERT_NULL(a->next);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, reverse_empty_and_single_are_safe_noops)
{
	t_dlist *lst = NULL;
	t_dlist *only = make_int_node(1);

	ft_dlstreverse(&lst);
	ASSERT_NULL(lst);
	ft_dlstadd_back(&lst, only);
	ft_dlstreverse(&lst);
	ASSERT_EQ_PTR(lst, only);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, find_locates_matching_node)
{
	t_dlist *lst = NULL;
	t_dlist *target;
	int		key = 2;

	ft_dlstadd_back(&lst, make_int_node(1));
	target = make_int_node(2);
	ft_dlstadd_back(&lst, target);
	ft_dlstadd_back(&lst, make_int_node(3));
	ASSERT_EQ_PTR(ft_dlstfind(lst, &key, dlist_compare_int), target);
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, find_no_match_returns_null)
{
	t_dlist *lst = NULL;
	int		key = 99;

	ft_dlstadd_back(&lst, make_int_node(1));
	ASSERT_NULL(ft_dlstfind(lst, &key, dlist_compare_int));
	ASSERT_NULL(ft_dlstfind(NULL, &key, dlist_compare_int));
	ft_dlstclear(&lst, free_int);
}

TEST(dlist, at_returns_node_by_index)
{
	t_dlist *lst = NULL;
	t_dlist *a = make_int_node(1);
	t_dlist *b = make_int_node(2);
	t_dlist *c = make_int_node(3);

	ft_dlstadd_back(&lst, a);
	ft_dlstadd_back(&lst, b);
	ft_dlstadd_back(&lst, c);
	ASSERT_EQ_PTR(ft_dlstat(lst, 0), a);
	ASSERT_EQ_PTR(ft_dlstat(lst, 1), b);
	ASSERT_EQ_PTR(ft_dlstat(lst, 2), c);
	ASSERT_NULL(ft_dlstat(lst, 3));
	ft_dlstclear(&lst, free_int);
}
