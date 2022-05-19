/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:18:57 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/05/19 11:46:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int main(int argc, char const *argv[])
{
    T_NODE *root;
    
    root = BT_insert_node(root, &(int){10});
    BT_insert_node(root, &(int){20});
    BT_insert_node(root, &(int){30});
    BT_insert_node(root, &(int){40});
    BT_insert_node(root, &(int){50});
    BT_insert_node(root, &(int){60});

    BT_display_nodes(root);
    BT_delete_tree(root, false);
    printf("---\n");
}
