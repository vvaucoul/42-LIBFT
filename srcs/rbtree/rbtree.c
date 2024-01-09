/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:23:24 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:34:10 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

Node *createNode(void *data, Color color, Node *parent) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = color;
    newNode->left = newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}

RBTree *createRBTree(CompareFunc compare) {
    RBTree *newTree = (RBTree *)malloc(sizeof(RBTree));
    newTree->root = NULL;
    newTree->compare = compare;
    return newTree;
}

void rotateLeft(RBTree *tree, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (x->right != NULL)
        x->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(RBTree *tree, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (y->left != NULL)
        y->left->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        tree->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void fixInsert(RBTree *tree, Node *k) {
    Node *u;
    while (k->parent != NULL && k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u != NULL && u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rotateRight(tree, k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateLeft(tree, k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;
            if (u != NULL && u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
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

void insert(RBTree *tree, void *key) {
    Node *node = createNode(key, RED, NULL);
    Node *temp = tree->root;
    Node *parent = NULL;

    while (temp != NULL) {
        parent = temp;
        if (tree->compare(node->data, temp->data) < 0)
            temp = temp->left;
        else
            temp = temp->right;
    }

    node->parent = parent;

    if (parent == NULL)
        tree->root = node;
    else if (tree->compare(node->data, parent->data) < 0)
        parent->left = node;
    else
        parent->right = node;

    fixInsert(tree, node);
}

int is_left_child(Node *node) {
    return node == node->parent->left;
}

void freeNode(Node *node) {
    if (node == NULL)
        return;

    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

void freeRBTree(RBTree *tree) {
    if (tree == NULL)
        return;

    freeNode(tree->root);
    free(tree);
}

void printNode(Node *node) {
    if (node == NULL)
        return;

    printf("%d", *(int *)node->data);
    if (node->color == RED)
        printf("(R)");
    else
        printf("(B)");

    if (node->left != NULL)
        printf(" L: %d", *(int *)node->left->data);
    if (node->right != NULL)
        printf(" R: %d", *(int *)node->right->data);
    printf("\n");

    printNode(node->left);
    printNode(node->right);
}

void printRBTree(RBTree *tree) {
    if (tree == NULL)
        return;

    printNode(tree->root);
}

void printNodeIndented(Node *node, int indent) {
    if (node == NULL)
        return;

    printNodeIndented(node->right, indent + 4);

    for (int i = 0; i < indent; i++)
        printf(" ");

    printf("%d", *(int *)node->data);
    if (node->color == RED)
        printf("(R)");
    else
        printf("(B)");

    printf("\n");

    printNodeIndented(node->left, indent + 4);
}

void printRBTreeIndented(RBTree *tree) {
    if (tree == NULL || tree->root == NULL)
        return;

    printNodeIndented(tree->root, 0);
}
