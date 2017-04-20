/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handlers_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:09:03 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 18:10:27 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	long_option_flag(char *option)
{
	t_etarget target;

	if (ft_strequ(option, "help"))
		help_handler();
	else if (ft_strequ(option, "recursive"))
		g_flags |= RECURSIVE_FLAG;
	else if (ft_strequ(option, "all"))
		g_flags |= ALL_FLAG;
	else if (ft_strequ(option, "reverse"))
		g_flags |= REVERSE_FLAG;
	else
	{
		target.flag = '-';
		error_handler(FLAG_ERR, target);
	}
}

void	display_flag_handler_2(char f)
{
	if (f == 'g')
		g_flags |= SUPRESS_OWNER;
	if (g_flags & COLUMN_DISPLAY)
		g_flags &= ~COLUMN_DISPLAY;
	if (g_flags & ONE_ENTRY_PER_LINE)
		g_flags &= ~ONE_ENTRY_PER_LINE;
	g_flags |= LONG_LISTING_FLAG;
}

void	display_flag_handler(char f)
{
	if (f == '1')
	{
		if (g_flags & COLUMN_DISPLAY)
			g_flags &= ~COLUMN_DISPLAY;
		if (g_flags & LONG_LISTING_FLAG)
			g_flags &= ~LONG_LISTING_FLAG;
		g_flags |= ONE_ENTRY_PER_LINE;
	}
	else if (f == 'l' || f == 'g')
		display_flag_handler_2(f);
	else
	{
		if (g_flags & ONE_ENTRY_PER_LINE)
			g_flags &= ~ONE_ENTRY_PER_LINE;
		if (g_flags & LONG_LISTING_FLAG)
			g_flags &= ~LONG_LISTING_FLAG;
		g_flags |= COLUMN_DISPLAY;
	}
}
