/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 02:16:17 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/20 02:18:37 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	dir_display_4(t_dirs *dirs)
{
	t_etarget	target;

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
