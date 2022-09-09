/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 00:54:42 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/09/10 00:57:16 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist *ft_dlstnew(void *data)
{
    t_dlist *new;

    if (!(new = (t_dlist *)malloc(sizeof(t_dlist))))
        return (NULL);
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}