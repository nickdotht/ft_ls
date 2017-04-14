/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:32:37 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/13 23:59:25 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirs *new_dir(char *path, int status, int is_default, char *subdir_name)
{
  t_dirs *dir;
  struct stat f;

  MEMCHECK((dir = (t_dirs *)ft_memalloc(sizeof(t_dirs))));
  MEMCHECK((dir->name = ft_strdup(path)));
  MEMCHECK((dir->self = (t_files *)ft_memalloc(sizeof(t_files))));
  MEMCHECK((dir->self->name = ft_strdup(path)));
  if (status != IS_NONEXISTENT)
  {
    dir->self->is_dir_info = 1;
    if (subdir_name)
      MEMCHECK((dir->display_name = ft_strdup(subdir_name)));
  }
  if (status == IS_DIR)
  {
    // Check if this passed
    lstat(dir->name, &f);
    dir->date.mtv_sec = (unsigned long long)f.st_mtime;
    dir->date.mtv_nsec = (unsigned long long)f.st_mtimespec.tv_nsec;
    dir->date.atv_sec = (unsigned long long)f.st_atime;
    dir->date.atv_nsec = (unsigned long long)f.st_atimespec.tv_nsec;
    dir->date.ctv_sec = (unsigned long long)f.st_ctime;
    dir->date.ctv_nsec = (unsigned long long)f.st_ctimespec.tv_nsec;
    dir->date.birthtv_sec = (unsigned long long)f.st_birthtime;
    dir->date.birthtv_nsec = (unsigned long long)f.st_birthtimespec.tv_nsec;
    MEMCHECK((dir->self->display_name = ft_strdup(path)));
  }
  dir->status = status;
  dir->next = NULL;
  dir->is_default = is_default;
  dir->is_unreadable = 0;
  dir->total_blocks = 0;
  dir->file_count = 0;
  dir->max_file_len = 0;
  return (dir);
}

void add_dir(t_dirs **dirs, t_dirs *new) {
	t_dirs *tmp;
	t_dirs *head;

	tmp = *dirs;
	head = tmp;
  while (tmp->next)
  		tmp = tmp->next;
	tmp->next = new;
	*dirs = head;
}

void reverse_dirs(t_dirs **dirs)
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

void set_dir(char *path, t_dirs **dirs, char *subdir_name) {
  t_dirs *new;
  int status;
  struct stat s;

  status = IS_DIR;
  if (lstat(path, &s) == -1)
  {
    if (ENOENT == errno)
      status = IS_NONEXISTENT;
  }
  else
  {
    if (!S_ISDIR(s.st_mode))
      status = IS_NOTDIR;
  }
  new = new_dir(path, status, 0, subdir_name);
  if (!*dirs || (*dirs)->is_default)
    *dirs = new;
  else
    add_dir(dirs, new);
}

t_dirs *dir_handler(char **args, t_flags flags) {
  int i;
  t_dirs *dirs;
  t_etarget target;
  t_dirs *tmp;

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
  if (flags & FILE_SIZE_SORT)
  {
    tmp = dirs;
    while (tmp)
    {
      add_file(&tmp->self, &tmp, flags, IDLE_FORMAT);
      tmp = tmp->next;
    }
  }
  dir_sort(&dirs, flags);
  return (dirs);
}
