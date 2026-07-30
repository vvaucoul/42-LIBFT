/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary-tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 19:19:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2026/07/30 19:19:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct s_bt_node
{
    void                *data;
    struct s_bt_node    *left;
    struct s_bt_node    *right;
}   t_bt_node;

typedef struct s_bt
{
    t_bt_node   *root;
    CompareFunc compare;
    size_t      size;
}   t_bt;

/*******************************************************************************
 *                           BINARY_TREE - FUNCTIONS                           *
 ******************************************************************************/

t_bt        *BT_create(CompareFunc compare);
void        BT_insert(t_bt *tree, void *data);
void        *BT_delete(t_bt *tree, void *key, bool free_data);
t_bt_node   *BT_search(t_bt *tree, void *key);
bool        BT_contains(t_bt *tree, void *key);
t_bt_node   *BT_min_node(t_bt_node *node);
t_bt_node   *BT_max_node(t_bt_node *node);
size_t      BT_size(t_bt *tree);
size_t      BT_height(t_bt *tree);
bool        BT_is_empty(t_bt *tree);
bool        BT_is_valid(t_bt *tree);
void        BT_free(t_bt *tree, bool free_data);
void        BT_display_nodes(t_bt *tree, void (*print_data)(void *));

#endif
