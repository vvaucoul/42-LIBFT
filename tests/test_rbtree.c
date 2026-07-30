/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rbtree.c                                      :+:      :+:    :+:   */
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

static void collect_inorder(RBTree *tree, Node *node)
{
	if (!tree || node == tree->nil)
		return ;
	collect_inorder(tree, node->left);
	g_inorder[g_inorder_count++] = *(int *)node->data;
	collect_inorder(tree, node->right);
}

static RBTree *build_tree(int *values, size_t n)
{
	RBTree *tree = createRBTree(compare_int);
	size_t i;

	i = 0;
	while (i < n)
	{
		insert(tree, &values[i]);
		++i;
	}
	return (tree);
}

TEST(rbtree, insert_maintains_bst_order)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80, 5, 90};
	int sorted[9];
	RBTree *tree = build_tree(values, 9);

	g_inorder_count = 0;
	collect_inorder(tree, tree->root);
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

	freeRBTree(tree, false);
}

TEST(rbtree, root_is_always_black)
{
	int values[] = {1, 2, 3, 4, 5};
	RBTree *tree = createRBTree(compare_int);

	for (size_t i = 0; i < 5; ++i)
	{
		insert(tree, &values[i]);
		ASSERT_EQ_INT(tree->root->color, BLACK);
	}
	freeRBTree(tree, false);
}

TEST(rbtree, single_insert_becomes_root)
{
	int value = 42;
	RBTree *tree = createRBTree(compare_int);

	insert(tree, &value);
	ASSERT_NOT_NULL(tree->root);
	ASSERT_EQ_INT(*(int *)tree->root->data, 42);
	ASSERT_EQ_INT(tree->root->color, BLACK);
	freeRBTree(tree, false);
}

TEST(rbtree, is_left_child_on_non_root_nodes)
{
	int values[] = {10, 20, 30, 40, 50};
	RBTree *tree = build_tree(values, 5);

	ASSERT(is_left_child(tree->root->left));
	ASSERT(is_left_child(tree->root->right->left));
	ASSERT(!is_left_child(tree->root->right->right));
	freeRBTree(tree, false);
}

TEST(rbtree, is_left_child_on_root_is_now_safe)
{
	int value = 1;
	RBTree *tree = createRBTree(compare_int);

	insert(tree, &value);
	ASSERT(!is_left_child(tree->root));
	freeRBTree(tree, false);
}

TEST(rbtree, is_left_child_null_node_is_safe)
{
	ASSERT(!is_left_child(NULL));
}

TEST(rbtree, free_empty_tree_is_safe)
{
	RBTree *tree = createRBTree(compare_int);

	freeRBTree(tree, false);
}

TEST(rbtree, free_null_tree_is_safe)
{
	freeRBTree(NULL, false);
}

TEST(rbtree, size_tracks_inserts)
{
	int values[] = {5, 3, 8, 1, 4, 7, 9};
	RBTree *tree = createRBTree(compare_int);

	ASSERT_EQ_UINT(rbtree_size(tree), 0);
	ASSERT(rbtree_is_empty(tree));
	for (size_t i = 0; i < 7; ++i)
	{
		insert(tree, &values[i]);
		ASSERT_EQ_UINT(rbtree_size(tree), i + 1);
	}
	ASSERT(!rbtree_is_empty(tree));
	freeRBTree(tree, false);
}

TEST(rbtree, height_grows_logarithmically_not_linearly)
{
	int values[20];
	RBTree *tree;

	for (int i = 0; i < 20; ++i)
		values[i] = i;
	tree = build_tree(values, 20);
	/* A red-black tree of N nodes has height <= 2*log2(N+1); for N=20 that's <=9. */
	ASSERT_MSG(rbtree_height(tree) <= 9,
		"rbtree_height() = %zu for 20 sorted inserts, expected a balanced "
		"height (<=9), got something closer to a linear chain",
		rbtree_height(tree));
	freeRBTree(tree, false);
}

TEST(rbtree, search_finds_present_and_absent_keys)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80};
	int present = 30;
	int absent = 99;
	RBTree *tree = build_tree(values, 7);
	Node *found;

	found = rbtree_search(tree, &present);
	ASSERT_NOT_NULL(found);
	ASSERT_EQ_INT(*(int *)found->data, 30);
	ASSERT_NULL(rbtree_search(tree, &absent));
	ASSERT(rbtree_contains(tree, &present));
	ASSERT(!rbtree_contains(tree, &absent));
	freeRBTree(tree, false);
}

TEST(rbtree, search_on_empty_tree_returns_null)
{
	int key = 1;
	RBTree *tree = createRBTree(compare_int);

	ASSERT_NULL(rbtree_search(tree, &key));
	freeRBTree(tree, false);
}

TEST(rbtree, min_and_max_nodes)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80, 5, 90};
	RBTree *tree = build_tree(values, 9);

	ASSERT_EQ_INT(*(int *)rbtree_min_node(tree, tree->root)->data, 5);
	ASSERT_EQ_INT(*(int *)rbtree_max_node(tree, tree->root)->data, 90);
	freeRBTree(tree, false);
}

TEST(rbtree, successor_and_predecessor_walk_in_order)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80};
	int key = 30;
	RBTree *tree = build_tree(values, 7);
	Node *node = rbtree_search(tree, &key);
	Node *succ = rbtree_successor(tree, node);
	Node *pred = rbtree_predecessor(tree, node);

	ASSERT_NOT_NULL(succ);
	ASSERT_EQ_INT(*(int *)succ->data, 50);
	ASSERT_NOT_NULL(pred);
	ASSERT_EQ_INT(*(int *)pred->data, 20);
	freeRBTree(tree, false);
}

TEST(rbtree, successor_of_max_and_predecessor_of_min_are_null)
{
	int values[] = {50, 20, 70};
	RBTree *tree = build_tree(values, 3);
	Node *min = rbtree_min_node(tree, tree->root);
	Node *max = rbtree_max_node(tree, tree->root);

	ASSERT_NULL(rbtree_predecessor(tree, min));
	ASSERT_NULL(rbtree_successor(tree, max));
	freeRBTree(tree, false);
}

TEST(rbtree, is_valid_after_many_inserts)
{
	int values[64];
	RBTree *tree;

	for (int i = 0; i < 64; ++i)
		values[i] = (i * 37 + 11) % 64;
	tree = build_tree(values, 64);
	ASSERT(rbtree_is_valid(tree));
	ASSERT_EQ_UINT(rbtree_size(tree), 64);
	freeRBTree(tree, false);
}

TEST(rbtree, delete_leaf_node)
{
	int values[] = {50, 20, 70, 10, 30};
	int key = 10;
	RBTree *tree = build_tree(values, 5);
	void *removed = rbtree_delete(tree, &key);

	ASSERT_NOT_NULL(removed);
	ASSERT_EQ_INT(*(int *)removed, 10);
	ASSERT_NULL(rbtree_search(tree, &key));
	ASSERT_EQ_UINT(rbtree_size(tree), 4);
	ASSERT(rbtree_is_valid(tree));
	freeRBTree(tree, false);
}

TEST(rbtree, delete_node_with_two_children)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80};
	int key = 20;
	RBTree *tree = build_tree(values, 7);
	void *removed = rbtree_delete(tree, &key);

	ASSERT_NOT_NULL(removed);
	ASSERT_EQ_INT(*(int *)removed, 20);
	ASSERT_NULL(rbtree_search(tree, &key));
	ASSERT_EQ_UINT(rbtree_size(tree), 6);
	ASSERT(rbtree_is_valid(tree));
	freeRBTree(tree, false);
}

TEST(rbtree, delete_root_repeatedly_until_empty)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80, 5, 90};
	RBTree *tree = build_tree(values, 9);

	while (!rbtree_is_empty(tree))
	{
		void *removed = rbtree_delete(tree, tree->root->data);

		ASSERT_NOT_NULL(removed);
		ASSERT(rbtree_is_valid(tree));
	}
	ASSERT_EQ_UINT(rbtree_size(tree), 0);
	freeRBTree(tree, false);
}

TEST(rbtree, delete_absent_key_returns_null_and_does_not_shrink)
{
	int values[] = {50, 20, 70};
	int absent = 99;
	RBTree *tree = build_tree(values, 3);

	ASSERT_NULL(rbtree_delete(tree, &absent));
	ASSERT_EQ_UINT(rbtree_size(tree), 3);
	freeRBTree(tree, false);
}

TEST(rbtree, delete_from_empty_tree_is_safe)
{
	int key = 1;
	RBTree *tree = createRBTree(compare_int);

	ASSERT_NULL(rbtree_delete(tree, &key));
	freeRBTree(tree, false);
}

TEST(rbtree, insert_and_delete_interleaved_stays_valid)
{
	int values[30];
	RBTree *tree = createRBTree(compare_int);

	for (int i = 0; i < 30; ++i)
		values[i] = i;
	for (int i = 0; i < 30; ++i)
	{
		insert(tree, &values[i]);
		if (i % 3 == 2)
			rbtree_delete(tree, &values[i - 2]);
		ASSERT(rbtree_is_valid(tree));
	}
	freeRBTree(tree, false);
}

static int g_print_arg_int[8];

static void action_print(void)
{
	RBTree *tree = createRBTree(compare_int);

	for (int i = 0; i < 3; ++i)
		insert(tree, &g_print_arg_int[i]);
	printRBTree(tree, rbtree_print_int);
	freeRBTree(tree, false);
}

TEST(print_rbtree, print_int_writes_values_and_colors)
{
	char *out;

	g_print_arg_int[0] = 2;
	g_print_arg_int[1] = 1;
	g_print_arg_int[2] = 3;
	out = test_capture_fd1(action_print);
	ASSERT_NOT_NULL(out);
	ASSERT(strstr(out, "2(B)") != NULL);
	ASSERT(strstr(out, "1(R)") != NULL || strstr(out, "3(R)") != NULL);
	free(out);
}

static void action_print_indented(void)
{
	RBTree *tree = createRBTree(compare_int);

	for (int i = 0; i < 3; ++i)
		insert(tree, &g_print_arg_int[i]);
	printRBTreeIndented(tree, rbtree_print_int);
	freeRBTree(tree, false);
}

static void action_print_empty(void)
{
	RBTree *tree = createRBTree(compare_int);

	printRBTreeIndented(tree, rbtree_print_int);
	freeRBTree(tree, false);
}

TEST(print_rbtree, print_indented_on_empty_tree_writes_nothing)
{
	char *out = test_capture_fd1(action_print_empty);

	ASSERT_EQ_STR(out, "");
	free(out);
}

TEST(print_rbtree, print_indented_writes_all_values)
{
	char *out;

	g_print_arg_int[0] = 2;
	g_print_arg_int[1] = 1;
	g_print_arg_int[2] = 3;
	out = test_capture_fd1(action_print_indented);
	ASSERT_NOT_NULL(out);
	ASSERT(strstr(out, "1") != NULL);
	ASSERT(strstr(out, "2") != NULL);
	ASSERT(strstr(out, "3") != NULL);
	free(out);
}
