/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_handlers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 02:00:16 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 07:48:52 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	move_dir(t_dirs **dest_ref, t_dirs **source_ref)
{
	t_dirs *new;

	new = *source_ref;
	*source_ref = (*source_ref)->next;
	new->next = *dest_ref;
	*dest_ref = new;
}

void	handle_dir_merge_comparison(t_dirs **a, t_dirs **b, t_dirs **tmp)
{
	int comparison;

	comparison = ft_strcmp((*a)->name, (*b)->name) < 0;
	if (g_flags & MODIFICATION_DATE_SORT)
	{
		comparison = modification_date_sort((*a)->name, (*b)->name,
			(*a)->date, (*b)->date);
		if (g_flags & CREATION_DATE_SORT)
			comparison = creation_date_sort((*a)->name, (*b)->name,
			(*a)->date, (*b)->date);
		else if (g_flags & LAST_ACCESS_DATE_SORT)
			comparison = last_access_date_sort((*a)->name, (*b)->name,
			(*a)->date, (*b)->date);
		else if (g_flags & LAST_STATUS_CHANGE_SORT)
			comparison = last_status_change_sort((*a)->name, (*b)->name,
			(*a)->date, (*b)->date);
	}
	else if (g_flags & FILE_SIZE_SORT)
	{
		comparison = (*a)->self->f.st_size >= (*b)->self->f.st_size;
		if ((*a)->self->f.st_size == (*b)->self->f.st_size)
			comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
	}
	move_dir(tmp, comparison ? a : b);
}

t_dirs	*merge_splitted_dirs(t_dirs *a, t_dirs *b)
{
	t_dirs *res;
	t_dirs **tmp;

	res = NULL;
	tmp = &res;
	while (1)
	{
		if (!a)
		{
			*tmp = b;
			break ;
		}
		else if (!b)
		{
			*tmp = a;
			break ;
		}
		handle_dir_merge_comparison(&a, &b, tmp);
		tmp = &((*tmp)->next);
	}
	return (res);
}

void	split_dirs(t_dirs *source_ref, t_dirs **front_ref, t_dirs **back_ref)
{
	t_dirs *slow;
	t_dirs *fast;

	slow = source_ref;
	fast = source_ref->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front_ref = source_ref;
	*back_ref = slow->next;
	slow->next = NULL;
}

void	dir_sort(t_dirs **dirs)
{
	t_dirs *head;
	t_dirs *a;
	t_dirs *b;

	head = *dirs;
	if (!head || !head->next)
		return ;
	split_dirs(head, &a, &b);
	dir_sort(&a);
	dir_sort(&b);
	*dirs = merge_splitted_dirs(a, b);
}
