/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:54:14 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 18:08:48 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_flag_handler_2(char f)
{
	if (f == 'u')
	{
		if (g_flags & CREATION_DATE_SORT)
			g_flags &= ~CREATION_DATE_SORT;
		if (g_flags & LAST_STATUS_CHANGE_SORT)
			g_flags &= ~LAST_STATUS_CHANGE_SORT;
		g_flags |= LAST_ACCESS_DATE_SORT;
	}
	else if (f == 'c')
	{
		if (g_flags & CREATION_DATE_SORT)
			g_flags &= ~CREATION_DATE_SORT;
		if (g_flags & LAST_ACCESS_DATE_SORT)
			g_flags &= ~LAST_ACCESS_DATE_SORT;
		g_flags |= LAST_STATUS_CHANGE_SORT;
	}
}

void	sort_flag_handler(char f)
{
	if (f == 't' && !(g_flags & FILE_SIZE_SORT))
		g_flags |= MODIFICATION_DATE_SORT;
	else if (f == 'U')
	{
		if (g_flags & LAST_ACCESS_DATE_SORT)
			g_flags &= ~LAST_ACCESS_DATE_SORT;
		if (g_flags & LAST_STATUS_CHANGE_SORT)
			g_flags &= ~LAST_STATUS_CHANGE_SORT;
		g_flags |= CREATION_DATE_SORT;
	}
	else if (f == 'u' || f == 'c')
		sort_flag_handler_2(f);
	else
	{
		if (g_flags & MODIFICATION_DATE_SORT)
			g_flags &= ~MODIFICATION_DATE_SORT;
		g_flags |= FILE_SIZE_SORT;
	}
}

void	set_flag_2(char f)
{
	if (f == 'r')
		g_flags |= REVERSE_FLAG;
	else if (f == 'n')
		g_flags |= DISPLAY_UID_AND_GID;
	else if (f == 'A')
		g_flags |= HIDE_CURR_AND_PREV_DIRS;
	else if (f == 'a')
		g_flags |= ALL_FLAG;
	else
		g_flags |= COLORED_OUTPUT;
}

void	set_flag(char *arg)
{
	int			i;
	t_etarget	target;

	if (ft_strstartswith(arg, "--") && arg[2])
		return (long_option_flag(arg + 2));
	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'R')
			g_flags |= RECURSIVE_FLAG;
		else if (arg[i] == 'a' || arg[i] == 'r' || arg[i] == 'n' ||
			arg[i] == 'A' || arg[i] == 'G')
			set_flag_2(arg[i]);
		else if (arg[i] == 'U' || arg[i] == 't' || arg[i] == 'u' ||
			arg[i] == 'c' || arg[i] == 'S')
			sort_flag_handler(arg[i]);
		else if (arg[i] == '1' || arg[i] == 'l' || arg[i] == 'C' ||
			arg[i] == 'g')
			display_flag_handler(arg[i]);
		else
		{
			target.flag = arg[i];
			error_handler(FLAG_ERR, target);
		}
	}
}

int		flag_handler(char **args)
{
	int i;

	i = -1;
	g_flags |= COLUMN_DISPLAY;
	while (args[++i])
	{
		if (args[i][0] != '-')
			break ;
		if (ft_strequ(args[i], "--"))
		{
			i++;
			break ;
		}
		if (args[i][0] == '-' && args[i][1])
			set_flag(args[i]);
		else
			break ;
	}
	return (i > 0 ? i + 1 : 1);
}
