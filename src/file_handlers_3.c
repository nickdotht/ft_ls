/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handlers_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 07:17:52 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 17:53:19 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	get_file_entry_type(int mode)
{
	if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

void	reverse_files(t_files **files)
{
	t_files *curr;
	t_files *next;
	t_files *prev;

	prev = NULL;
	curr = *files;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*files = prev;
}

char	get_correct_character(int mode, int is_exec, int is_sticky)
{
	if (mode & is_exec)
	{
		if (mode & is_sticky)
			return ('s');
		else
			return ('x');
	}
	else
	{
		if (mode & is_sticky)
			return ('S');
		else
			return ('-');
	}
}

char	third_permission_mode_handler(int mode, int user_type)
{
	if (user_type == ISUSR)
		return (get_correct_character(mode, S_IXUSR, S_ISUID));
	else if (user_type == ISGRP)
		return (get_correct_character(mode, S_IXGRP, S_ISGID));
	else
	{
		if (mode & S_IXOTH)
		{
			if (mode & S_ISTXT)
				return ('t');
			else
				return ('x');
		}
		else
		{
			if (mode & S_ISTXT)
				return ('T');
			else
				return ('-');
		}
	}
}

void	add_file_info(t_dirs **dirs)
{
	t_dirs *tmp;

	tmp = *dirs;
	while (tmp)
	{
		add_file(&tmp->self, &tmp, IDLE_FORMAT);
		tmp = tmp->next;
	}
}
