/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handlers_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 04:10:39 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/20 02:15:37 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	dir_display_5(t_dirs *dirs)
{
	if (g_flags & LONG_LISTING_FLAG)
	{
		long_listing_display(dirs->format, dirs->files,
			dirs->has_chr_or_blk);
	}
	else
	{
		if (dirs->files->has_nonprintable_chars)
			print_handler(1, "%s\n", 0, dirs->files->display_name);
		else
			print_handler(1, "%s\n", 0, dirs->files->name);
	}
}

void	dir_display_3(t_dirs *dirs)
{
	t_etarget	target;

	if (dirs->files->status == IS_NONEXISTENT)
	{
		if (dirs->files->has_nonprintable_chars)
		{
			MEMCHECK((target.file = ft_strdup(dirs->files->display_name)));
		}
		else
		{
			MEMCHECK((target.file = ft_strdup(dirs->files->name)));
		}
		error_handler(NONEXISTENT_ERR, target);
		free(target.file);
	}
	else if (dirs->files->status == IS_UNREADABLE)
		dir_display_4(dirs);
	else
		dir_display_5(dirs);
}

void	dir_display(t_dirs *head, t_dirs *dirs)
{
	if (dir_display_2(head, dirs))
		return ;
	while (dirs->files)
	{
		dir_display_3(dirs);
		dirs->files = dirs->files->next;
	}
}

void	display_handler(t_dirs *head, t_dirs *dirs, int target)
{
	t_etarget	etarget;
	t_dirs		*tmp;

	if (target == IS_NONEXISTENT)
	{
		tmp = dirs;
		while (tmp)
		{
			if (tmp->status == IS_NONEXISTENT)
			{
				MEMCHECK((etarget.file = ft_strdup(tmp->name)));
				error_handler(NONEXISTENT_ERR, etarget);
				memory_handler(etarget.file, ERROR_MEM);
			}
			tmp = tmp->next;
		}
	}
	else if (target == IS_NOTDIR)
		nondir_display(dirs, has_dirs(dirs));
	else
		dir_display(head, dirs);
}

void	ft_display(t_dirs *dirs)
{
	t_dirs *tmp;

	display_handler(NULL, dirs, IS_NONEXISTENT);
	if (g_flags & REVERSE_FLAG)
		reverse_dirs(&dirs);
	display_handler(NULL, dirs, IS_NOTDIR);
	tmp = dirs;
	while (tmp)
	{
		if (tmp->status == IS_DIR)
		{
			tmp->files = file_handler(tmp);
			if (g_flags & REVERSE_FLAG)
				reverse_files(&tmp->files);
			display_handler(dirs, tmp, IS_DIR);
			tmp->next = subdir_handler(tmp->next, &(tmp->sub_dirs));
			if (!is_last_dir(tmp))
				print_handler(1, "\n", 0, NULL);
		}
		tmp = tmp->next;
	}
}
