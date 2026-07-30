/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_binarytree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

static int g_inorder[64];
static int g_inorder_count;

static void collect_inorder(t_bt_node *node)
{
	if (!node)
		return ;
	collect_inorder(node->left);
	g_inorder[g_inorder_count++] = *(int *)node->data;
	collect_inorder(node->right);
}

static t_bt *build_tree(int *values, size_t n)
{
	t_bt *tree = BT_create(compare_int);
	size_t i;

	i = 0;
	while (i < n)
	{
		BT_insert(tree, &values[i]);
		++i;
	}
	return (tree);
}

TEST(binarytree, create_null_compare_returns_null)
{
	ASSERT_NULL(BT_create(NULL));
}

TEST(binarytree, insert_maintains_bst_order)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80, 5, 90};
	int sorted[9];
	t_bt *tree = build_tree(values, 9);

	g_inorder_count = 0;
	collect_inorder(tree->root);
	ASSERT_EQ_INT(g_inorder_count, 9);

	memcpy(sorted, values, sizeof(values));
	for (int i = 0; i < 9; ++i)
		for (int j = i + 1; j < 9; ++j)
			if (sorted[j] < sorted[i])
			{
				int tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
	for (int i = 0; i < 9; ++i)
		ASSERT_EQ_INT(g_inorder[i], sorted[i]);

	BT_free(tree, false);
}

TEST(binarytree, insert_same_value_twice_is_a_noop)
{
	int value = 1;
	int same_value = 1;
	t_bt *tree = BT_create(compare_int);

	BT_insert(tree, &value);
	BT_insert(tree, &same_value);
	ASSERT_EQ_UINT(BT_size(tree), 1);
	ASSERT_NULL(tree->root->left);
	ASSERT_NULL(tree->root->right);
	BT_free(tree, false);
}

TEST(binarytree, size_tracks_inserts)
{
	int values[] = {5, 3, 8, 1, 4, 7, 9};
	t_bt *tree = BT_create(compare_int);

	ASSERT_EQ_UINT(BT_size(tree), 0);
	ASSERT(BT_is_empty(tree));
	for (size_t i = 0; i < 7; ++i)
	{
		BT_insert(tree, &values[i]);
		ASSERT_EQ_UINT(BT_size(tree), i + 1);
	}
	ASSERT(!BT_is_empty(tree));
	BT_free(tree, false);
}

TEST(binarytree, search_finds_present_and_absent_keys)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80};
	int present = 30;
	int absent = 99;
	t_bt *tree = build_tree(values, 7);
	t_bt_node *found;

	found = BT_search(tree, &present);
	ASSERT_NOT_NULL(found);
	ASSERT_EQ_INT(*(int *)found->data, 30);
	ASSERT_NULL(BT_search(tree, &absent));
	ASSERT(BT_contains(tree, &present));
	ASSERT(!BT_contains(tree, &absent));
	BT_free(tree, false);
}

TEST(binarytree, search_on_empty_tree_returns_null)
{
	int key = 1;
	t_bt *tree = BT_create(compare_int);

	ASSERT_NULL(BT_search(tree, &key));
	BT_free(tree, false);
}

TEST(binarytree, min_and_max_nodes)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80, 5, 90};
	t_bt *tree = build_tree(values, 9);

	ASSERT_EQ_INT(*(int *)BT_min_node(tree->root)->data, 5);
	ASSERT_EQ_INT(*(int *)BT_max_node(tree->root)->data, 90);
	ASSERT_NULL(BT_min_node(NULL));
	ASSERT_NULL(BT_max_node(NULL));
	BT_free(tree, false);
}

TEST(binarytree, is_valid_after_many_inserts)
{
	int values[64];
	t_bt *tree;

	for (int i = 0; i < 64; ++i)
		values[i] = (i * 37 + 11) % 64;
	tree = build_tree(values, 64);
	ASSERT(BT_is_valid(tree));
	BT_free(tree, false);
}

TEST(binarytree, height_grows_with_insertion_order)
{
	int sorted_values[10];
	t_bt *chain;

	for (int i = 0; i < 10; ++i)
		sorted_values[i] = i;
	/* Plain BST with no self-balancing: sorted input degenerates to a chain. */
	chain = build_tree(sorted_values, 10);
	ASSERT_EQ_UINT(BT_height(chain), 10);
	BT_free(chain, false);
}

TEST(binarytree, delete_leaf_node)
{
	int values[] = {50, 20, 70, 10, 30};
	int key = 10;
	t_bt *tree = build_tree(values, 5);
	void *removed = BT_delete(tree, &key, false);

	ASSERT_NOT_NULL(removed);
	ASSERT_EQ_INT(*(int *)removed, 10);
	ASSERT_NULL(BT_search(tree, &key));
	ASSERT_EQ_UINT(BT_size(tree), 4);
	ASSERT(BT_is_valid(tree));
	BT_free(tree, false);
}

/* Uses heap-allocated payloads so a use-after-free/double-free would be observable. */
TEST(binarytree, delete_node_with_two_children_frees_only_the_removed_value)
{
	int *values[7];
	t_bt *tree = BT_create(compare_int);
	int key = 20;
	void *removed;

	int seed[] = {50, 20, 70, 10, 30, 60, 80};
	for (int i = 0; i < 7; ++i)
	{
		values[i] = malloc(sizeof(int));
		*values[i] = seed[i];
		BT_insert(tree, values[i]);
	}
	removed = BT_delete(tree, &key, true);
	ASSERT_NULL(removed);
	ASSERT_NULL(BT_search(tree, &key));
	ASSERT_EQ_UINT(BT_size(tree), 6);
	ASSERT(BT_is_valid(tree));
	for (int i = 0; i < 7; ++i)
		if (seed[i] != key)
			ASSERT(BT_contains(tree, &seed[i]));
	BT_free(tree, false);
}

TEST(binarytree, delete_root_repeatedly_until_empty)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80, 5, 90};
	t_bt *tree = build_tree(values, 9);

	while (!BT_is_empty(tree))
	{
		void *removed = BT_delete(tree, tree->root->data, false);

		ASSERT_NOT_NULL(removed);
		ASSERT(BT_is_valid(tree));
	}
	ASSERT_EQ_UINT(BT_size(tree), 0);
	BT_free(tree, false);
}

TEST(binarytree, delete_absent_key_returns_null_and_does_not_shrink)
{
	int values[] = {50, 20, 70};
	int absent = 99;
	t_bt *tree = build_tree(values, 3);

	ASSERT_NULL(BT_delete(tree, &absent, false));
	ASSERT_EQ_UINT(BT_size(tree), 3);
	BT_free(tree, false);
}

TEST(binarytree, delete_from_empty_tree_is_safe)
{
	int key = 1;
	t_bt *tree = BT_create(compare_int);

	ASSERT_NULL(BT_delete(tree, &key, false));
	BT_free(tree, false);
}

TEST(binarytree, insert_and_delete_interleaved_stays_valid)
{
	int values[30];
	t_bt *tree = BT_create(compare_int);

	for (int i = 0; i < 30; ++i)
		values[i] = i;
	for (int i = 0; i < 30; ++i)
	{
		BT_insert(tree, &values[i]);
		if (i % 3 == 2)
			BT_delete(tree, &values[i - 2], false);
		ASSERT(BT_is_valid(tree));
	}
	BT_free(tree, false);
}

TEST(binarytree, free_empty_tree_is_safe)
{
	t_bt *tree = BT_create(compare_int);

	BT_free(tree, false);
}

TEST(binarytree, free_null_tree_is_safe)
{
	BT_free(NULL, false);
}

static int g_print_arg_int[8];

static void action_display(void)
{
	t_bt *tree = BT_create(compare_int);

	for (int i = 0; i < 3; ++i)
		BT_insert(tree, &g_print_arg_int[i]);
	BT_display_nodes(tree, rbtree_print_int);
	BT_free(tree, false);
}

TEST(print_binarytree, display_nodes_prints_in_order)
{
	char *out;

	g_print_arg_int[0] = 2;
	g_print_arg_int[1] = 1;
	g_print_arg_int[2] = 3;
	out = test_capture_fd1(action_display);
	ASSERT_NOT_NULL(out);
	ASSERT_EQ_STR(out, "1\n2\n3\n");
	free(out);
}

static void action_display_empty(void)
{
	t_bt *tree = BT_create(compare_int);

	BT_display_nodes(tree, rbtree_print_int);
	BT_free(tree, false);
}

TEST(print_binarytree, display_nodes_on_empty_tree_writes_nothing)
{
	char *out = test_capture_fd1(action_display_empty);

	ASSERT_EQ_STR(out, "");
	free(out);
}
