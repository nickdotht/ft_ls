/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handlers_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 07:10:46 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 07:48:51 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	move_file(t_files **dest_ref, t_files **source_ref)
{
	t_files *new;

	new = *source_ref;
	*source_ref = (*source_ref)->next;
	new->next = *dest_ref;
	*dest_ref = new;
}

void	handle_file_merge_comparison(t_files **a, t_files **b, t_files **tmp)
{
	int comparison;

	comparison = ft_strcmp((*a)->name, (*b)->name) < 0;
	if (g_flags & MODIFICATION_DATE_SORT)
	{
		comparison = modification_date_sort((*a)->name, (*b)->name, (*a)->date,
			(*b)->date);
		if (g_flags & CREATION_DATE_SORT)
			comparison = creation_date_sort((*a)->name, (*b)->name, (*a)->date,
			(*b)->date);
		else if (g_flags & LAST_ACCESS_DATE_SORT)
			comparison = last_access_date_sort((*a)->name, (*b)->name,
				(*a)->date, (*b)->date);
		else if (g_flags & LAST_STATUS_CHANGE_SORT)
			comparison = last_status_change_sort((*a)->name, (*b)->name,
				(*a)->date, (*b)->date);
	}
	else if (g_flags & FILE_SIZE_SORT)
	{
		comparison = (*a)->f.st_size > (*b)->f.st_size;
		if ((*a)->f.st_size == (*b)->f.st_size)
			comparison = ft_strcmp((*a)->name, (*b)->name) < 0;
	}
	move_file(tmp, comparison ? a : b);
}

t_files	*merge_splitted_files(t_files *a, t_files *b)
{
	t_files *res;
	t_files **tmp;

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
		handle_file_merge_comparison(&a, &b, tmp);
		tmp = &((*tmp)->next);
	}
	return (res);
}

void	split_file(t_files *source_ref, t_files **front_ref,
	t_files **back_ref)
{
	t_files *slow;
	t_files *fast;

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

void	file_sort(t_files **files)
{
	t_files *head;
	t_files *a;
	t_files *b;

	head = *files;
	if (!head || !head->next)
		return ;
	split_file(head, &a, &b);
	file_sort(&a);
	file_sort(&b);
	*files = merge_splitted_files(a, b);
}
