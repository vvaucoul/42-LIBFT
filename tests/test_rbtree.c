/* ************************************************************************** */
/*   test_rbtree.c - srcs/rbtree/rbtree.c                                    */
/*                                                                            */
/*   NOTE: includes/libft.h declares `RBTree *createRBTree();` (K&R style,   */
/*   "unspecified arguments"), but the real definition in rbtree.c is        */
/*   `createRBTree(CompareFunc compare)` - the header is stale. Calling it   */
/*   with one argument (as below, and as the project's own tests/main.c     */
/*   already did before this suite existed) compiles fine and is correct;   */
/*   calling it with zero arguments would read garbage for `compare`.       */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

static int g_inorder[64];
static int g_inorder_count;

static void collect_inorder(Node *node)
{
	if (!node)
		return ;
	collect_inorder(node->left);
	g_inorder[g_inorder_count++] = *(int *)node->data;
	collect_inorder(node->right);
}

TEST(rbtree, insert_maintains_bst_order)
{
	int values[] = {50, 20, 70, 10, 30, 60, 80, 5, 90};
	int sorted[9];
	RBTree *tree = createRBTree(compare_int);

	ASSERT_NOT_NULL(tree);
	for (size_t i = 0; i < 9; ++i)
		insert(tree, &values[i]);

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

	freeRBTree(tree);
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
	freeRBTree(tree);
}

TEST(rbtree, single_insert_becomes_root)
{
	int value = 42;
	RBTree *tree = createRBTree(compare_int);

	insert(tree, &value);
	ASSERT_NOT_NULL(tree->root);
	ASSERT_EQ_INT(*(int *)tree->root->data, 42);
	ASSERT_EQ_INT(tree->root->color, BLACK);
	freeRBTree(tree);
}

TEST(rbtree, is_left_child_on_non_root_nodes)
{
	int values[] = {10, 20, 30, 40, 50};
	RBTree *tree = createRBTree(compare_int);

	for (size_t i = 0; i < 5; ++i)
		insert(tree, &values[i]);
	/* Matches the shape asserted in the project's original tests/main.c */
	ASSERT(is_left_child(tree->root->left));
	ASSERT(is_left_child(tree->root->right->left));
	ASSERT(!is_left_child(tree->root->right->right));
	freeRBTree(tree);
}

/* is_left_child() does `return node == node->parent->left;` with no NULL
** guard: calling it on the root (whose ->parent is NULL) dereferences a
** NULL pointer. Isolated in its own test - fork+alarm reports the crash
** cleanly rather than taking the suite down. */
TEST(rbtree, is_left_child_on_root_known_bug_isolated)
{
	int value = 1;
	RBTree *tree = createRBTree(compare_int);

	insert(tree, &value);
	is_left_child(tree->root);
	freeRBTree(tree);
}

TEST(rbtree, free_empty_tree_is_safe)
{
	RBTree *tree = createRBTree(compare_int);

	freeRBTree(tree);
}

TEST(rbtree, free_null_tree_is_safe)
{
	freeRBTree(NULL);
}
