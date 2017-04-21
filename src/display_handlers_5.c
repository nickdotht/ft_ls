/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handlers_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 21:02:15 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/20 21:06:04 by jrameau          ###   ########.fr       */
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
