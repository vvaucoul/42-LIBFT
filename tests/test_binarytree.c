/* ************************************************************************** */
/*   test_binarytree.c - srcs/binary-tree/binary-tree.c                      */
/*                                                                            */
/*   BT_insert_node()/BT_delete_node() order by raw POINTER ADDRESS          */
/*   (`data < root->data`), not by any dereferenced value - so these tests   */
/*   insert pointers into a plain array, where &arr[i] < &arr[j] iff i < j,  */
/*   to get a predictable, testable ordering. `_g_bt.root` is never written  */
/*   by anything in this file, so BT_get_root() always returns NULL - it's  */
/*   not a per-tree accessor, just dead. Deletions below always pass        */
/*   delete_data=0 because our node payloads point into a stack array;      */
/*   free()-ing a stack address would itself crash.                         */
/* ************************************************************************** */

#include <libft.h>
#include "framework/test_framework.h"

static int	*g_visit[8];
static int	g_visit_count;

static void collect_inorder(T_NODE *node)
{
	if (!node)
		return ;
	collect_inorder(node->left);
	g_visit[g_visit_count++] = (int *)node->data;
	collect_inorder(node->right);
}

TEST(binarytree, new_node_has_no_children)
{
	int value = 42;
	T_NODE *node = BT_new_node(&value);

	ASSERT_NOT_NULL(node);
	ASSERT_EQ_PTR(node->data, &value);
	ASSERT_NULL(node->left);
	ASSERT_NULL(node->right);
	free(node);
}

TEST(binarytree, insert_orders_by_pointer_address)
{
	int arr[5] = {0, 1, 2, 3, 4};
	T_NODE *root = NULL;

	root = BT_insert_node(root, &arr[2]);
	root = BT_insert_node(root, &arr[0]);
	root = BT_insert_node(root, &arr[4]);
	root = BT_insert_node(root, &arr[1]);
	root = BT_insert_node(root, &arr[3]);

	g_visit_count = 0;
	collect_inorder(root);
	ASSERT_EQ_INT(g_visit_count, 5);
	for (int i = 0; i < 5; ++i)
		ASSERT_EQ_PTR(g_visit[i], &arr[i]);

	BT_delete_tree(root, 0);
}

TEST(binarytree, insert_same_pointer_twice_is_noop)
{
	int arr[2] = {0, 1};
	T_NODE *root = NULL;

	root = BT_insert_node(root, &arr[0]);
	root = BT_insert_node(root, &arr[0]);
	ASSERT_NULL(root->left);
	ASSERT_NULL(root->right);
	BT_delete_tree(root, 0);
}

TEST(binarytree, delete_leaf_node)
{
	int arr[3] = {0, 1, 2};
	T_NODE *root = NULL;

	root = BT_insert_node(root, &arr[1]);
	root = BT_insert_node(root, &arr[0]);
	root = BT_insert_node(root, &arr[2]);
	root = BT_delete_node(root, &arr[0], 0);

	g_visit_count = 0;
	collect_inorder(root);
	ASSERT_EQ_INT(g_visit_count, 2);
	ASSERT_EQ_PTR(g_visit[0], &arr[1]);
	ASSERT_EQ_PTR(g_visit[1], &arr[2]);
	BT_delete_tree(root, 0);
}

/* Nothing in this file ever assigns to the module-global `_g_bt.root` -
** BT_get_root() always returns NULL, regardless of any tree built through
** BT_new_node/BT_insert_node. */
TEST(binarytree, get_root_is_always_null_known_bug)
{
	int arr[3] = {0, 1, 2};
	T_NODE *root = NULL;

	root = BT_insert_node(root, &arr[1]);
	root = BT_insert_node(root, &arr[0]);
	ASSERT_MSG(BT_get_root() == root,
		"BT_get_root() should return the tree just built, but the global "
		"_g_bt.root is never assigned anywhere and stays NULL");
	BT_delete_tree(root, 0);
}

/* BT_delete_tree(root, ...) does `root = NULL;` at the very end, but that
** only clears the function's own local parameter copy - the caller's
** variable still points at freed memory afterward. We only compare the
** pointer VALUE here (never dereference it) to stay safely inside defined
** behavior while still demonstrating the bug. */
TEST(binarytree, delete_tree_does_not_null_callers_pointer_known_bug)
{
	int arr[2] = {0, 1};
	T_NODE *root = NULL;

	root = BT_insert_node(root, &arr[0]);
	root = BT_insert_node(root, &arr[1]);
	BT_delete_tree(root, 0);
	ASSERT_MSG(root == NULL,
		"after BT_delete_tree(root, 0), the caller's `root` should be "
		"NULL, but BT_delete_tree only nulls its own local parameter");
}
