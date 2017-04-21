/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 00:01:01 by jrameau           #+#    #+#             */
/*   Updated: 2016/09/29 00:01:03 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddback(t_list **alst, t_list *new)
{
    t_list  *tmp;
    t_list  *head;

    tmp = *alst;
    head = tmp;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
	*alst = head;
}
