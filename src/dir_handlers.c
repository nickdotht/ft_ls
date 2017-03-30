/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:32:37 by jrameau           #+#    #+#             */
/*   Updated: 2017/03/29 23:48:10 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirs *new_dir(char *name, int status, int is_default)
{
  t_dirs *dir;
  struct stat f;

  MEMCHECK((dir = (t_dirs *)ft_memalloc(sizeof(t_dirs))));
  if (status != IS_NOTDIR)
  {
    MEMCHECK((dir->name = ft_strdup(name)));
  }
  else
  {
    MEMCHECK((dir->self = (t_files *)ft_memalloc(sizeof(t_files))));
    MEMCHECK((dir->self->name = ft_strdup(name))); 
  }
  if (status == IS_DIR)
    lstat(dir->name, &f);
  dir->format.date_month = 3;
  dir->format.date_day = 2;
  dir->format.date_hour = 2;
  dir->format.date_minute = 2;
  dir->format.date_year = 5;
  dir->status = status;
  dir->next = NULL;
  dir->date.tv_sec = (unsigned long long)f.st_mtime;
  dir->date.tv_nsec = (unsigned long long)f.st_mtimespec.tv_nsec;
  dir->is_default = is_default;
  dir->is_unreadable = 0;
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

void set_dir(char *arg, t_dirs **dirs) {
  t_dirs *new;
  int status;
  struct stat s;

  status = IS_DIR;
  if (lstat(arg, &s) == -1)
  {
    if (ENOENT == errno)
      status = IS_NONEXISTENT;
  }
  else
  {
    if (!S_ISDIR(s.st_mode))
      status = IS_NOTDIR;
  }
  new = new_dir(arg, status, 0);
  if (!*dirs || (*dirs)->is_default)
    *dirs = new;
  else
    add_dir(dirs, new);
}

t_dirs *dir_handler(char **args, t_flags flags) {
  int i;
  t_dirs *dirs;

  i = -1;
  dirs = new_dir(".", IS_DIR, 1);
  while (args[++i])
      set_dir(args[i], &dirs);
  dir_sort(&dirs, flags);
  return (dirs);
}
