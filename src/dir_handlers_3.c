/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_handlers_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 03:58:18 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 07:26:53 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	initialize_dir(t_dirs **dir, int status, char *path, char *subdir_name)
{
	struct stat f;

	if (status != IS_NONEXISTENT)
	{
		lstat((*dir)->name, &f);
		date_initializer(&(*dir)->date, f);
		MEMCHECK(((*dir)->self->display_name = ft_strdup(path)));
		(*dir)->self->is_dir_info = 1;
		if (subdir_name)
			MEMCHECK(((*dir)->display_name = ft_strdup(subdir_name)));
	}
	(*dir)->status = status;
	(*dir)->is_unreadable = 0;
	(*dir)->total_blocks = 0;
	(*dir)->file_count = 0;
	(*dir)->has_valid_files = 0;
	(*dir)->max_file_len = 0;
	(*dir)->next = NULL;
}
