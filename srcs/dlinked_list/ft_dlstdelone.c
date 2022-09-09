/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 00:52:44 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/10 00:58:01 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_dlstdelone(t_dlist **alst, void (*del)(void *))
{
    if (alst && *alst)
    {
        if (del)
            del((*alst)->data);
        free(*alst);
        *alst = NULL;
    }
}