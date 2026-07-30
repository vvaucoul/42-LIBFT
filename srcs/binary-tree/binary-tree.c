/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary-tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static t_bt_node *bt_new_node(void *data)
{
    t_bt_node *node;

    if (!(node = malloc(sizeof(t_bt_node))))
        return (NULL);
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

t_bt *BT_create(CompareFunc compare)
{
    t_bt *tree;

    if (!compare)
        return (NULL);
    if (!(tree = malloc(sizeof(t_bt))))
        return (NULL);
    tree->root = NULL;
    tree->compare = compare;
    tree->size = 0;
    return (tree);
}

/* Duplicate keys (compare == 0) are a silent no-op, matching the original
** implementation's behaviour (it only ever recursed on `<`/`>`). */
static t_bt_node *bt_insert_node(t_bt *tree, t_bt_node *node, void *data,
        bool *inserted)
{
    int cmp;

    if (!node)
    {
        *inserted = true;
        return (bt_new_node(data));
    }
    cmp = tree->compare(data, node->data);
    if (cmp < 0)
        node->left = bt_insert_node(tree, node->left, data, inserted);
    else if (cmp > 0)
        node->right = bt_insert_node(tree, node->right, data, inserted);
    return (node);
}

void BT_insert(t_bt *tree, void *data)
{
    bool inserted;

    if (!tree)
        return ;
    inserted = false;
    tree->root = bt_insert_node(tree, tree->root, data, &inserted);
    if (inserted)
        ++tree->size;
}

t_bt_node *BT_search(t_bt *tree, void *key)
{
    t_bt_node *cur;
    int cmp;

    if (!tree)
        return (NULL);
    cur = tree->root;
    while (cur)
    {
        cmp = tree->compare(key, cur->data);
        if (cmp == 0)
            return (cur);
        cur = cmp < 0 ? cur->left : cur->right;
    }
    return (NULL);
}

bool BT_contains(t_bt *tree, void *key)
{
    return (BT_search(tree, key) != NULL);
}

t_bt_node *BT_min_node(t_bt_node *node)
{
    if (!node)
        return (NULL);
    while (node->left)
        node = node->left;
    return (node);
}

t_bt_node *BT_max_node(t_bt_node *node)
{
    if (!node)
        return (NULL);
    while (node->right)
        node = node->right;
    return (node);
}

static t_bt_node *bt_delete_node(t_bt *tree, t_bt_node *node, void *key,
        void **out_removed)
{
    t_bt_node *tmp;
    void *discard;
    int cmp;

    if (!node)
        return (NULL);
    cmp = tree->compare(key, node->data);
    if (cmp < 0)
        node->left = bt_delete_node(tree, node->left, key, out_removed);
    else if (cmp > 0)
        node->right = bt_delete_node(tree, node->right, key, out_removed);
    else if (!node->left || !node->right)
    {
        *out_removed = node->data;
        tmp = node->left ? node->left : node->right;
        free(node);
        return (tmp);
    }
    else
    {
        tmp = BT_min_node(node->right);
        *out_removed = node->data;
        node->data = tmp->data;
        node->right = bt_delete_node(tree, node->right, tmp->data, &discard);
    }
    return (node);
}

void *BT_delete(t_bt *tree, void *key, bool free_data)
{
    void *removed;

    if (!tree || !BT_search(tree, key))
        return (NULL);
    removed = NULL;
    tree->root = bt_delete_node(tree, tree->root, key, &removed);
    --tree->size;
    if (free_data)
    {
        free(removed);
        return (NULL);
    }
    return (removed);
}

size_t BT_size(t_bt *tree)
{
    if (!tree)
        return (0);
    return (tree->size);
}

bool BT_is_empty(t_bt *tree)
{
    return (!tree || !tree->root);
}

static size_t bt_node_height(t_bt_node *node)
{
    size_t left_h;
    size_t right_h;

    if (!node)
        return (0);
    left_h = bt_node_height(node->left);
    right_h = bt_node_height(node->right);
    return (1 + (left_h > right_h ? left_h : right_h));
}

size_t BT_height(t_bt *tree)
{
    if (!tree)
        return (0);
    return (bt_node_height(tree->root));
}

static bool bt_check_order(t_bt *tree, t_bt_node *node, void *min,
        bool has_min, void *max, bool has_max)
{
    if (!node)
        return (true);
    if (has_min && tree->compare(node->data, min) < 0)
        return (false);
    if (has_max && tree->compare(node->data, max) > 0)
        return (false);
    if (!bt_check_order(tree, node->left, min, has_min, node->data, true))
        return (false);
    return (bt_check_order(tree, node->right, node->data, true, max,
            has_max));
}

bool BT_is_valid(t_bt *tree)
{
    if (!tree)
        return (false);
    return (bt_check_order(tree, tree->root, NULL, false, NULL, false));
}

static void bt_free_node(t_bt_node *node, bool free_data)
{
    if (!node)
        return ;
    bt_free_node(node->left, free_data);
    bt_free_node(node->right, free_data);
    if (free_data)
        free(node->data);
    free(node);
}

void BT_free(t_bt *tree, bool free_data)
{
    if (!tree)
        return ;
    bt_free_node(tree->root, free_data);
    free(tree);
}

static void bt_display(t_bt_node *node, void (*print_data)(void *))
{
    if (!node)
        return ;
    bt_display(node->left, print_data);
    print_data(node->data);
    printf("\n");
    bt_display(node->right, print_data);
}

void BT_display_nodes(t_bt *tree, void (*print_data)(void *))
{
    if (!tree || !print_data)
        return ;
    bt_display(tree->root, print_data);
}
