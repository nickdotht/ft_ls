/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handlers_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:40:08 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 17:50:57 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_file_2(t_dirs **dirs, t_files **curr_file, char *dir_name)
{
	int file_name_len;

	if ((g_flags & LONG_LISTING_FLAG) && !(*curr_file)->is_dir_info)
	{
		if ((*dirs)->status == IS_DIR)
			(*dirs)->total_blocks += (*curr_file)->f.st_blocks;
	}
	else
	{
		(*dirs)->file_count++;
		file_name_len = ft_strlen((*curr_file)->name);
		if (file_name_len > (*dirs)->max_file_len)
			(*dirs)->max_file_len = file_name_len;
	}
	if (S_ISDIR((*curr_file)->f.st_mode) && (g_flags & RECURSIVE_FLAG) &&
		!ft_strequ((*curr_file)->name, "..") &&
		!ft_strequ((*curr_file)->name, "."))
	{
		set_dir(ft_pathjoin(dir_name, (*curr_file)->name),
			&((*dirs)->sub_dirs), (*curr_file)->name);
	}
}

void	add_file(t_files **curr_file, t_dirs **dirs, int format_option)
{
	char	*dir_name;
	char	*file_path;

	dir_name = (*dirs)->name;
	file_path = (*curr_file)->is_dir_info ? (*curr_file)->name :
		ft_pathjoin(dir_name, (*curr_file)->name);
	if (lstat(file_path, &(*curr_file)->f) < 0)
	{
		if (errno == ENOENT)
			(*curr_file)->status = IS_NONEXISTENT;
		else if (errno == EACCES)
			(*curr_file)->status = IS_UNREADABLE;
		return ;
	}
	(*dirs)->has_valid_files = 1;
	MEMCHECK(((*curr_file)->modes = ft_strnew(11)));
	get_file_info(curr_file, dirs, file_path, format_option);
	add_file_2(dirs, curr_file, dir_name);
}

char	*get_entry_name(char *path)
{
	char	**parts;
	int		i;

	MEMCHECK((parts = ft_strsplit(path, '/')));
	i = -1;
	while (parts[++i])
	{
		if (!parts[i + 1])
			return (parts[i]);
	}
	return (path);
}

void	file_handler_2(t_files **files, DIR *dir, t_dirs *dirs,
	struct dirent *sd)
{
	t_files	**tmp;
	int		format_option;

	tmp = files;
	format_option = INIT_FORMAT;
	while ((sd = readdir(dir)))
	{
		if (g_flags & HIDE_CURR_AND_PREV_DIRS && !(g_flags & ALL_FLAG) &&
			(ft_strequ(sd->d_name, ".") || ft_strequ(sd->d_name, "..")))
			continue ;
		if (!(g_flags & ALL_FLAG) && !(g_flags & HIDE_CURR_AND_PREV_DIRS)
			&& sd->d_name[0] == '.')
			continue ;
		MEMCHECK(((*tmp = (t_files *)ft_memalloc(sizeof(t_files)))));
		if (has_nonprintable_chars(sd->d_name, ft_strlen(sd->d_name)))
		{
			(*tmp)->display_name = serialize_name(sd->d_name,
				ft_strlen(sd->d_name));
			(*tmp)->has_nonprintable_chars = 1;
		}
		(*tmp)->name = ft_strdup(sd->d_name);
		add_file(tmp, &dirs, format_option);
		format_option = UPDATE_FORMAT;
		tmp = &((*tmp)->next);
	}
}

t_files	*file_handler(t_dirs *dirs)
{
	DIR				*dir;
	t_files			*files;
	struct dirent	*sd;

	if (!(dir = opendir(dirs->name)))
	{
		dirs->is_unreadable = 1;
		MEMCHECK((dirs->display_name = get_entry_name(dirs->name)));
		return (NULL);
	}
	files = NULL;
	sd = NULL;
	file_handler_2(&files, dir, dirs, sd);
	if (dir)
		closedir(dir);
	file_sort(&files);
	return (files);
}
