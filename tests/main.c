/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:18:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2024/01/09 01:34:20 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <string.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1024

// Function to check the properties of a red-black tree
void check_properties(RBTree *tree) {
    // Property 1: Every node is either red or black
    // Property 2: The root is black
    assert(tree->root->color == BLACK);

    // Property 3: All leaves are black (omitted, as leaves are NULL)
    // Property 4: If a node is red, then both its children are black
    // Property 5: Every path from a node to its descendant leaves contains the same number of black nodes
    // (omitted, as they require a more complex recursive function to check)
}

int main() {
    RBTree *tree = createRBTree(compare_int);

    // Insert values
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        insert(tree, &values[i]);
        check_properties(tree);
    }

    printRBTreeIndented(tree);

    // Check structure of tree
    assert(tree->root->data == &values[1]);
    assert(is_left_child(tree->root->left));
    assert(tree->root->right->data == &values[3]);
    assert(is_left_child(tree->root->right->left));
    assert(!is_left_child(tree->root->right->right));

    // Free tree
    // (you need to implement this function)
    freeRBTree(tree);
}

// Parser *__parser;

// if ((__parser = ft_parser(argc, argv)) == NULL)
//     return (1);

// ForEachArgs(__parser)
// {
//     char buffer[128];
//     printf("\n%zu: %s\n", arg->index, arg->str);

//     ft_bzero(buffer, 128);

//     if (!(sscanf(arg->str, "value:%s", buffer)))
//         sscanf(arg->str, "-%s", buffer);
//     printf("Buffer: %s\n", buffer);
// }

// ft_free_parser(&__parser);
// }
