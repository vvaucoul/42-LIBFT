/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* Shared BLACK sentinel leaf standing in for every NULL child/parent, so
** node pointers are always valid and insert/delete stay branch-free. */
static Node *rb_create_nil(void)
{
    Node *nil;

    if (!(nil = malloc(sizeof(Node))))
        return (NULL);
    nil->data = NULL;
    nil->color = BLACK;
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;
    return (nil);
}

Node *createNode(RBTree *tree, void *data, Color color, Node *parent)
{
    Node *node;

    if (!tree || !(node = malloc(sizeof(Node))))
        return (NULL);
    node->data = data;
    node->color = color;
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = parent;
    return (node);
}

RBTree *createRBTree(CompareFunc compare)
{
    RBTree *tree;

    if (!compare)
        return (NULL);
    if (!(tree = malloc(sizeof(RBTree))))
        return (NULL);
    if (!(tree->nil = rb_create_nil()))
    {
        free(tree);
        return (NULL);
    }
    tree->root = tree->nil;
    tree->compare = compare;
    tree->size = 0;
    return (tree);
}

void rotateLeft(RBTree *tree, Node *x)
{
    Node *y;

    y = x->right;
    x->right = y->left;
    if (y->left != tree->nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == tree->nil)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(RBTree *tree, Node *y)
{
    Node *x;

    x = y->left;
    y->left = x->right;
    if (x->right != tree->nil)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == tree->nil)
        tree->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void fixInsert(RBTree *tree, Node *k)
{
    Node *u;

    while (k->parent->color == RED)
    {
        if (k->parent == k->parent->parent->right)
        {
            u = k->parent->parent->left;
            if (u->color == RED)
            {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else
            {
                if (k == k->parent->left)
                {
                    k = k->parent;
                    rotateRight(tree, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateLeft(tree, k->parent->parent);
            }
        }
        else
        {
            u = k->parent->parent->right;
            if (u->color == RED)
            {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else
            {
                if (k == k->parent->right)
                {
                    k = k->parent;
                    rotateLeft(tree, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateRight(tree, k->parent->parent);
            }
        }
        if (k == tree->root)
            break;
    }
    tree->root->color = BLACK;
}

void insert(RBTree *tree, void *data)
{
    Node *node;
    Node *cur;
    Node *parent;

    if (!tree)
        return ;
    cur = tree->root;
    parent = tree->nil;
    while (cur != tree->nil)
    {
        parent = cur;
        if (tree->compare(data, cur->data) < 0)
            cur = cur->left;
        else
            cur = cur->right;
    }
    if (!(node = createNode(tree, data, RED, parent)))
        return ;
    if (parent == tree->nil)
        tree->root = node;
    else if (tree->compare(node->data, parent->data) < 0)
        parent->left = node;
    else
        parent->right = node;
    ++tree->size;
    fixInsert(tree, node);
}

/*******************************************************************************
 *                                   SEARCH                                    *
 ******************************************************************************/

Node *rbtree_search(RBTree *tree, void *key)
{
    Node *cur;
    int cmp;

    if (!tree)
        return (NULL);
    cur = tree->root;
    while (cur != tree->nil)
    {
        cmp = tree->compare(key, cur->data);
        if (cmp == 0)
            return (cur);
        cur = cmp < 0 ? cur->left : cur->right;
    }
    return (NULL);
}

bool rbtree_contains(RBTree *tree, void *key)
{
    return (rbtree_search(tree, key) != NULL);
}

/*******************************************************************************
 *                        MIN / MAX / SUCCESSOR / PREDECESSOR                 *
 ******************************************************************************/

static Node *tree_minimum(RBTree *tree, Node *node)
{
    while (node->left != tree->nil)
        node = node->left;
    return (node);
}

static Node *tree_maximum(RBTree *tree, Node *node)
{
    while (node->right != tree->nil)
        node = node->right;
    return (node);
}

Node *rbtree_min_node(RBTree *tree, Node *node)
{
    if (!tree || !node || node == tree->nil)
        return (NULL);
    return (tree_minimum(tree, node));
}

Node *rbtree_max_node(RBTree *tree, Node *node)
{
    if (!tree || !node || node == tree->nil)
        return (NULL);
    return (tree_maximum(tree, node));
}

Node *rbtree_successor(RBTree *tree, Node *node)
{
    Node *parent;

    if (!tree || !node || node == tree->nil)
        return (NULL);
    if (node->right != tree->nil)
        return (tree_minimum(tree, node->right));
    parent = node->parent;
    while (parent != tree->nil && node == parent->right)
    {
        node = parent;
        parent = parent->parent;
    }
    return (parent == tree->nil ? NULL : parent);
}

Node *rbtree_predecessor(RBTree *tree, Node *node)
{
    Node *parent;

    if (!tree || !node || node == tree->nil)
        return (NULL);
    if (node->left != tree->nil)
        return (tree_maximum(tree, node->left));
    parent = node->parent;
    while (parent != tree->nil && node == parent->left)
    {
        node = parent;
        parent = parent->parent;
    }
    return (parent == tree->nil ? NULL : parent);
}

/*******************************************************************************
 *                                    DELETE                                  *
 ******************************************************************************/

static void rb_transplant(RBTree *tree, Node *u, Node *v)
{
    if (u->parent == tree->nil)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

void fixDelete(RBTree *tree, Node *x)
{
    Node *w;

    while (x != tree->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(tree, x->parent);
                x = tree->root;
            }
        }
        else
        {
            w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void *rbtree_delete(RBTree *tree, void *key)
{
    Node *z;
    Node *y;
    Node *x;
    Color y_original_color;
    void *removed_data;

    if (!tree || !(z = rbtree_search(tree, key)))
        return (NULL);
    removed_data = z->data;
    y = z;
    y_original_color = y->color;
    if (z->left == tree->nil)
    {
        x = z->right;
        rb_transplant(tree, z, z->right);
    }
    else if (z->right == tree->nil)
    {
        x = z->left;
        rb_transplant(tree, z, z->left);
    }
    else
    {
        y = tree_minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else
        {
            rb_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_original_color == BLACK)
        fixDelete(tree, x);
    --tree->size;
    return (removed_data);
}

/*******************************************************************************
 *                            SIZE / HEIGHT / VALIDATION                      *
 ******************************************************************************/

size_t rbtree_size(RBTree *tree)
{
    if (!tree)
        return (0);
    return (tree->size);
}

bool rbtree_is_empty(RBTree *tree)
{
    return (!tree || tree->root == tree->nil);
}

static size_t node_height(RBTree *tree, Node *node)
{
    size_t left_h;
    size_t right_h;

    if (node == tree->nil)
        return (0);
    left_h = node_height(tree, node->left);
    right_h = node_height(tree, node->right);
    return (1 + (left_h > right_h ? left_h : right_h));
}

size_t rbtree_height(RBTree *tree)
{
    if (!tree)
        return (0);
    return (node_height(tree, tree->root));
}

static bool check_bst_order(RBTree *tree, Node *node, void *min, bool has_min,
    void *max, bool has_max)
{
    if (node == tree->nil)
        return (true);
    if (has_min && tree->compare(node->data, min) < 0)
        return (false);
    if (has_max && tree->compare(node->data, max) > 0)
        return (false);
    if (!check_bst_order(tree, node->left, min, has_min, node->data, true))
        return (false);
    return (check_bst_order(tree, node->right, node->data, true, max, has_max));
}

static int check_black_height(RBTree *tree, Node *node, bool *ok)
{
    int left_bh;
    int right_bh;

    if (node == tree->nil)
        return (1);
    if (node->color == RED
        && (node->left->color == RED || node->right->color == RED))
        *ok = false;
    left_bh = check_black_height(tree, node->left, ok);
    right_bh = check_black_height(tree, node->right, ok);
    if (left_bh != right_bh)
        *ok = false;
    return (left_bh + (node->color == BLACK ? 1 : 0));
}

bool rbtree_is_valid(RBTree *tree)
{
    bool ok;

    if (!tree)
        return (false);
    if (tree->root == tree->nil)
        return (true);
    if (tree->root->color != BLACK)
        return (false);
    ok = true;
    check_black_height(tree, tree->root, &ok);
    if (!ok)
        return (false);
    return (check_bst_order(tree, tree->root, NULL, false, NULL, false));
}

/*******************************************************************************
 *                                     MISC                                   *
 ******************************************************************************/

int is_left_child(Node *node)
{
    if (!node || !node->parent)
        return (0);
    return (node == node->parent->left);
}

void freeNode(RBTree *tree, Node *node, bool free_data)
{
    if (!tree || !node || node == tree->nil)
        return ;
    freeNode(tree, node->left, free_data);
    freeNode(tree, node->right, free_data);
    if (free_data)
        free(node->data);
    free(node);
}

void freeRBTree(RBTree *tree, bool free_data)
{
    if (!tree)
        return ;
    freeNode(tree, tree->root, free_data);
    free(tree->nil);
    free(tree);
}

/*******************************************************************************
 *                                    PRINTING                                *
 ******************************************************************************/

void rbtree_print_int(void *data)
{
    printf("%d", *(int *)data);
}

void printNode(RBTree *tree, Node *node, void (*print_data)(void *))
{
    if (!tree || node == tree->nil)
        return ;
    print_data(node->data);
    printf(node->color == RED ? "(R)" : "(B)");
    if (node->left != tree->nil)
    {
        printf(" L:");
        print_data(node->left->data);
    }
    if (node->right != tree->nil)
    {
        printf(" R:");
        print_data(node->right->data);
    }
    printf("\n");
    printNode(tree, node->left, print_data);
    printNode(tree, node->right, print_data);
}

void printRBTree(RBTree *tree, void (*print_data)(void *))
{
    if (!tree)
        return ;
    printNode(tree, tree->root, print_data);
}

void printNodeIndented(RBTree *tree, Node *node, int indent,
    void (*print_data)(void *))
{
    int i;

    if (!tree || node == tree->nil)
        return ;
    printNodeIndented(tree, node->right, indent + 4, print_data);
    i = 0;
    while (i < indent)
    {
        printf(" ");
        ++i;
    }
    print_data(node->data);
    printf(node->color == RED ? "(R)\n" : "(B)\n");
    printNodeIndented(tree, node->left, indent + 4, print_data);
}

void printRBTreeIndented(RBTree *tree, void (*print_data)(void *))
{
    if (!tree || tree->root == tree->nil)
        return ;
    printNodeIndented(tree, tree->root, 0, print_data);
}
