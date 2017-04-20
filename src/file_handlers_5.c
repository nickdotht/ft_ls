/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handlers_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:51:20 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 17:53:54 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_link_file(t_files **curr_file, char *file_path)
{
	char		buff[256];
	int			link_len;

	(*curr_file)->is_link = 1;
	if ((link_len = readlink(file_path, buff, 256)) == -1)
		exit(2);
	if (has_nonprintable_chars(buff, link_len))
	{
		MEMCHECK(((*curr_file)->linked_to = serialize_name(buff, link_len)));
	}
	else
	{
		MEMCHECK(((*curr_file)->linked_to = ft_strndup(buff, link_len)));
	}
}

void	get_file_info(t_files **curr_file, t_dirs **dirs, char *file_path,
	int format_option)
{
	struct stat	f;

	f = (*curr_file)->f;
	file_permission_handler(curr_file, file_path, f);
	(*curr_file)->owner = getpwuid(f.st_uid) ?
		ft_strdup(getpwuid(f.st_uid)->pw_name) :
		NULL;
	(*curr_file)->group = getgrgid(f.st_gid) ?
		ft_strdup(getgrgid(f.st_gid)->gr_name) :
		NULL;
	if (S_ISCHR(f.st_mode) || S_ISBLK(f.st_mode))
	{
		(*curr_file)->is_chr_or_blk = 1;
		(*dirs)->has_chr_or_blk = 1;
	}
	if (S_ISLNK(f.st_mode))
		get_link_file(curr_file, file_path);
	file_date_handler(&((*curr_file)->date), f);
	format_handler(&(*dirs)->format, *curr_file, format_option);
}
