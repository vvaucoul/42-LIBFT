/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 00:53:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/10 00:58:10 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
    t_dlist *tmp;

    if (!lst)
        return ;
    tmp = lst;
    while (tmp)
    {
        f(tmp->data);
        tmp = tmp->next;
    }
}