/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:32:37 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 04:07:35 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirs		*new_dir(char *path, int status, int is_default, char *subdir_name)
{
	t_dirs		*dir;
	DIR			*dr;

	MEMCHECK((dir = (t_dirs *)ft_memalloc(sizeof(t_dirs))));
	MEMCHECK((dir->name = ft_strdup(path)));
	MEMCHECK((dir->self = (t_files *)ft_memalloc(sizeof(t_files))));
	MEMCHECK((dir->self->name = ft_strdup(path)));
	if (status == IS_LINK)
	{
		if (!(dr = opendir(dir->name)) || g_flags & LONG_LISTING_FLAG)
			status = IS_NOTDIR;
		else
			status = IS_DIR;
		if (dr)
			closedir(dr);
	}
	dir->is_default = is_default;
	initialize_dir(&dir, status, path, subdir_name);
	return (dir);
}

void		add_dir(t_dirs **dirs, t_dirs *new)
{
	t_dirs *tmp;
	t_dirs *head;

	tmp = *dirs;
	head = tmp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	*dirs = head;
}

void		reverse_dirs(t_dirs **dirs)
{
	t_dirs *curr;
	t_dirs *next;
	t_dirs *prev;

	prev = NULL;
	curr = *dirs;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*dirs = prev;
}

void		set_dir(char *path, t_dirs **dirs, char *subdir_name)
{
	t_dirs		*new;
	int			status;
	struct stat	f;

	status = IS_DIR;
	if (lstat(path, &f) == -1)
	{
		if (ENOENT == errno)
			status = IS_NONEXISTENT;
	}
	else
	{
		if (!S_ISDIR(f.st_mode))
			status = IS_NOTDIR;
	}
	if (S_ISLNK(f.st_mode))
		status = IS_LINK;
	new = new_dir(path, status, 0, subdir_name);
	if (!*dirs || (*dirs)->is_default)
		*dirs = new;
	else
		add_dir(dirs, new);
}

t_dirs		*dir_handler(char **args)
{
	int			i;
	t_dirs		*dirs;
	t_etarget	target;

	dirs = new_dir(".", IS_DIR, 1, 0);
	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '\0')
		{
			MEMCHECK((target.file = ft_strdup("fts_open")));
			error_handler(NONEXISTENT_ERR, target);
			free(target.file);
			exit(1);
		}
		set_dir(args[i], &dirs, NULL);
	}
	if (g_flags & FILE_SIZE_SORT)
		file_size_sort(&dirs);
	dir_sort(&dirs);
	return (dirs);
}
