/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handlers_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 04:10:39 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 22:29:51 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	nondir_column_display(t_dirs *dirs, int should_separate)
{
	t_dirs		*tmp;
	int			file_count;
	t_entries	entries;
	int			max_file_len;
	int			i;

	file_count = 0;
	max_file_len = 0;
	tmp = dirs;
	while (tmp)
	{
		if (tmp->status == IS_NOTDIR)
		{
			++file_count;
			if ((int)ft_strlen(tmp->self->name) > max_file_len)
				max_file_len = ft_strlen(tmp->self->name);
		}
		tmp = tmp->next;
	}
	MEMCHECK((entries.file_names = (char **)ft_memalloc(sizeof(char *) *
		file_count)));
	tmp = dirs;
	i = -1;
	while (tmp)
	{
		if (tmp->status == IS_NOTDIR)
		{
			if (tmp->self->has_nonprintable_chars)
				entries.file_names[++i] = ft_strdup(tmp->self->display_name);
			else
				entries.file_names[++i] = ft_strdup(tmp->self->name);
		}
		tmp = tmp->next;
	}
	if (file_count)
		column_display(entries, file_count, max_file_len, IS_NOTDIR);
	free(entries.file_names);
	if (file_count && should_separate)
		print_handler(1, "\n", 0, NULL);
}

void	nondir_display(t_dirs *dirs, int should_separate)
{
	t_dirs		*tmp;
	t_format	nondir_format;

	if (g_flags & COLUMN_DISPLAY)
		return (nondir_column_display(dirs, should_separate));
	nondir_format = get_nondir_format(&dirs);
	tmp = dirs;
	while (tmp)
	{
		if (tmp->status == IS_NOTDIR)
		{
			if (g_flags & LONG_LISTING_FLAG)
			{
				long_listing_display(nondir_format, tmp->self,
					tmp->has_chr_or_blk);
			}
			else
			{
				if (tmp->self->has_nonprintable_chars)
					print_handler(1, "%s\n", 0, tmp->self->display_name);
				else
					print_handler(1, "%s\n", 0, tmp->self->name);
			}
			if (is_last_nondir(tmp) && should_separate)
				print_handler(1, "\n", 0, NULL);
		}
		tmp = tmp->next;
	}
}

void	dir_display(t_dirs *head, t_dirs *dirs)
{
	t_entries	entries;
	t_etarget	target;

	if (head->next)
		print_handler(1, "%s:\n", 0, dirs->name);
	if (dirs->is_unreadable)
	{
		MEMCHECK((target.file = ft_strdup(dirs->display_name)));
		return (error_handler(FILE_ACCESS_ERR, target));
		free(target.file);
	}
	if ((g_flags & LONG_LISTING_FLAG) && dirs->files && dirs->has_valid_files)
		print_handler(1, "total %d\n", 0, ft_itoa(dirs->total_blocks));
	if (g_flags & COLUMN_DISPLAY)
	{
		entries.files = dirs->files;
		if (dirs->file_count)
		{
			return (column_display(entries, dirs->file_count,
				dirs->max_file_len, IS_DIR));
		}
	}
	while (dirs->files)
	{
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
		{
			if (dirs->files->has_nonprintable_chars)
			{
				MEMCHECK((target.file = ft_strdup(dirs->files->display_name)));
			}
			else
			{
				MEMCHECK((target.file = ft_strdup(dirs->files->name)));
			}
			error_handler(FILE_ACCESS_ERR, target);
			free(target.file);
		}
		else
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
