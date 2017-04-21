/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handlers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:30:10 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/20 21:06:50 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	long_listing_display_2(t_format format, t_files *file,
	int has_chr_or_blk)
{
	if (file->is_chr_or_blk)
	{
		print_handler(1, " %ld, ", format.major,
			ft_itoa((long)major(file->f.st_rdev)));
		print_handler(1, "%ld ", format.minor,
			ft_itoa((long)minor(file->f.st_rdev)));
	}
	else
	{
		print_handler(1, "%ld ", has_chr_or_blk ? format.major + format.minor +
		format.file_size + 2 : format.file_size, ft_itoa(file->f.st_size));
	}
	print_handler(1, "%s ", format.date_month, file->date.month);
	print_handler(1, "%s ", format.date_day, file->date.day);
	date_display_handler(format, file->date);
	if (file->has_nonprintable_chars)
		display_file_name(file->f, file->display_name);
	else
		display_file_name(file->f, file->name);
	if (file->is_link)
		print_handler(1, " -> %s", 0, file->linked_to);
	print_handler(1, "\n", 0, NULL);
}

void	long_listing_display(t_format format, t_files *file,
	int has_chr_or_blk)
{
	print_handler(1, "%s ", 0, file->modes);
	print_handler(1, "%ld ", format.link, ft_itoa(file->f.st_nlink));
	if (!(g_flags & SUPRESS_OWNER))
	{
		if (file->owner && !(g_flags & DISPLAY_UID_AND_GID))
			lprint_handler(1, "%s  ", format.owner, file->owner);
		else
		{
			lprint_handler(1, "%d  ", format.user_id,
				ft_itoa((int)file->f.st_uid));
		}
	}
	if (file->group && !(g_flags & DISPLAY_UID_AND_GID))
		lprint_handler(1, "%s  ", format.group, file->group);
	else
	{
		lprint_handler(1, "%d  ", format.group_id,
			ft_itoa((int)file->f.st_gid));
	}
	long_listing_display_2(format, file, has_chr_or_blk);
}

int		*get_rows_cols(int max_file_len, int file_count)
{
	struct winsize	w;
	int				*rows_cols;
	int				term_width;

	rows_cols = (int *)ft_memalloc(sizeof(int) * 2);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	term_width = w.ws_col;
	rows_cols[1] = term_width / (max_file_len + 1);
	if (!rows_cols[1])
		rows_cols[1] = 1;
	if ((max_file_len + 1) * file_count < term_width)
		rows_cols[1] = file_count;
	rows_cols[0] = file_count / rows_cols[1];
	if (file_count % rows_cols[1])
		++rows_cols[0];
	return (rows_cols);
}

void	print_columns(t_entries entries, int *data, char **arr, int target)
{
	int		i;
	int		j;
	int		pos;
	int		*rows_cols;

	rows_cols = get_rows_cols(data[1], data[0]);
	pos = 0;
	i = -1;
	while (++i < rows_cols[0])
	{
		j = -1;
		pos = i;
		while (++j < rows_cols[1])
		{
			lprint_handler(1, "%s ", data[1], target == IS_DIR ?
				arr[pos] :
				entries.file_names[pos]);
			pos += rows_cols[0];
			if (pos >= data[0])
				break ;
		}
		print_handler(1, "\n", 0, NULL);
	}
}

void	column_display(t_entries entries, int file_count,
	int max_file_len, int target)
{
	int		i;
	char	**arr;
	int		*data;

	arr = NULL;
	if (target == IS_DIR)
	{
		MEMCHECK((arr = (char **)ft_memalloc(sizeof(char *) *
			(file_count + 1))));
		i = 0;
		while (entries.files)
		{
			if (entries.files->has_nonprintable_chars)
				arr[i++] = ft_strdup(entries.files->display_name);
			else
				arr[i++] = ft_strdup(entries.files->name);
			entries.files = entries.files->next;
		}
	}
	data = (int *)ft_memalloc(sizeof(int) * 2);
	data[0] = file_count;
	data[1] = max_file_len;
	print_columns(entries, data, arr, target);
	if (target == IS_DIR)
		free(arr);
}
