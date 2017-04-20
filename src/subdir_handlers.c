/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subdir_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:56:45 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 20:56:47 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirs		*subdir_handler(t_dirs *next, t_dirs **sub_dirs)
{
	t_dirs *tmp;

	if (!*sub_dirs)
		return (next);
	dir_sort(sub_dirs);
	if (g_flags & REVERSE_FLAG)
		reverse_dirs(sub_dirs);
	tmp = *sub_dirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = next;
	return (*sub_dirs);
}
