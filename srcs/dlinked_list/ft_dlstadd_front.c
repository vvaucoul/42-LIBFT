/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 00:51:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/10 00:51:51 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
    new->next = *lst;
    if (*lst)
        (*lst)->prev = new;
    *lst = new;
}