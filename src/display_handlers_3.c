/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 02:15:20 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/20 02:18:47 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	nondir_column_display_2(t_dirs *dirs, t_entries *entries)
{
	t_dirs	*tmp;
	int		i;

	tmp = dirs;
	i = -1;
	while (tmp)
	{
		if (tmp->status == IS_NOTDIR)
		{
			if (tmp->self->has_nonprintable_chars)
				entries->file_names[++i] = ft_strdup(tmp->self->display_name);
			else
				entries->file_names[++i] = ft_strdup(tmp->self->name);
		}
		tmp = tmp->next;
	}
}

void	nondir_column_display(t_dirs *dirs, int should_separate)
{
	t_dirs		*tmp;
	t_entries	entries;
	t_norm		norm;

	norm.d1 = 0;
	norm.d2 = 0;
	tmp = dirs;
	while (tmp)
	{
		if (tmp->status == IS_NOTDIR)
		{
			++norm.d1;
			if ((int)ft_strlen(tmp->self->name) > (int)norm.d2)
				norm.d2 = (void *)ft_strlen(tmp->self->name);
		}
		tmp = tmp->next;
	}
	MEMCHECK((entries.file_names = (char **)ft_memalloc(sizeof(char *) *
		(int)norm.d1)));
	nondir_column_display_2(dirs, &entries);
	if ((int)norm.d1)
		column_display(entries, (int)norm.d1, (int)norm.d2, IS_NOTDIR);
	free(entries.file_names);
	if (norm.d1 && should_separate)
		print_handler(1, "\n", 0, NULL);
}

void	nondir_display_2(t_dirs *tmp, t_format nondir_format,
	int should_separate)
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
			nondir_display_2(tmp, nondir_format, should_separate);
		tmp = tmp->next;
	}
}

int		dir_display_2(t_dirs *head, t_dirs *dirs)
{
	t_entries	entries;
	t_etarget	target;

	if (head->next)
		print_handler(1, "%s:\n", 0, dirs->name);
	if (dirs->is_unreadable)
	{
		MEMCHECK((target.file = ft_strdup(dirs->display_name)));
		error_handler(FILE_ACCESS_ERR, target);
		return (1);
	}
	if ((g_flags & LONG_LISTING_FLAG) && dirs->files && dirs->has_valid_files)
		print_handler(1, "total %d\n", 0, ft_itoa(dirs->total_blocks));
	if (g_flags & COLUMN_DISPLAY)
	{
		entries.files = dirs->files;
		if (dirs->file_count)
		{
			column_display(entries, dirs->file_count,
				dirs->max_file_len, IS_DIR);
			return (1);
		}
	}
	return (0);
}
