/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handlers_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:30:10 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/20 02:52:24 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	date_display_handler(t_format format, t_date date)
{
	struct timeval		tp;
	unsigned long long	curr_date;
	unsigned long long	six_months;
	unsigned long long	t;

	gettimeofday(&tp, NULL);
	curr_date = (unsigned long long)tp.tv_sec;
	six_months = 15778476;
	t = date.mtv_sec;
	if (g_flags & CREATION_DATE_SORT)
		t = date.birthtv_sec;
	if (g_flags & LAST_ACCESS_DATE_SORT)
		t = date.atv_sec;
	if (g_flags & LAST_STATUS_CHANGE_SORT)
		t = date.ctv_sec;
	if (t <= (curr_date - six_months) || t >= (curr_date + six_months))
		print_handler(1, "%s ", format.date_year, date.year);
	else
	{
		print_handler(1, "%s:", format.date_hour, date.hour);
		print_handler(1, "%s ", format.date_minute, date.minute);
	}
}

void	display_file_name(struct stat f, char *name)
{
	if (!(g_flags & COLORED_OUTPUT))
		return (print_handler(1, "%s", 0, name));
	if (S_ISDIR(f.st_mode))
		print_handler(1, ANSI_COLOR_BOLD_CYAN "%s" ANSI_COLOR_RESET, 0, name);
	else if (S_ISLNK(f.st_mode))
		print_handler(1, ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET, 0, name);
	else if (S_ISSOCK(f.st_mode))
		print_handler(1, ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, 0, name);
	else if (S_ISFIFO(f.st_mode))
		print_handler(1, ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, 0, name);
	else if (S_ISBLK(f.st_mode))
		print_handler(1, ANSI_COLOR_BOLD_GREEN "%s" ANSI_COLOR_RESET, 0, name);
	else if (S_ISCHR(f.st_mode))
		print_handler(1, ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, 0, name);
	else if (S_ISREG(f.st_mode) && f.st_mode & S_IXUSR)
		print_handler(1, ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, 0, name);
	else
		print_handler(1, "%s", 0, name);
}

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

void	column_display(t_entries entries, int file_count,
	int max_file_len, int target)
{
	struct winsize	w;
	int				cols;
	int				rows;
	char			**arr;
	int				term_width;
	int				i;
	int				pos;
	int				j;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	term_width = w.ws_col;
	cols = term_width / (max_file_len + 1);
	if (!cols)
		cols = 1;
	if ((max_file_len + 1) * file_count < term_width)
		cols = file_count;
	rows = file_count / cols;
	if (file_count % cols)
		++rows;
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
	pos = 0;
	i = -1;
	while (++i < rows)
	{
		j = -1;
		pos = i;
		while (++j < cols)
		{
			lprint_handler(1, "%s ", max_file_len, target == IS_DIR ?
				arr[pos] :
				entries.file_names[pos]);
			pos += rows;
			if (pos >= file_count)
				break ;
		}
		print_handler(1, "\n", 0, NULL);
	}
	if (target == IS_DIR)
		free(arr);
}
