/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:32:37 by jrameau           #+#    #+#             */
/*   Updated: 2017/03/27 16:47:58 by jrameau          ###   ########.fr       */
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
  dir->status = status;
  dir->next = NULL;
  dir->date.unix_format = (unsigned long long)f.st_mtime;
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

int dir_cmp(const void *a, const void *b)
{
    char * const *first = a;
    char * const *second = b;
    return (ft_strcmp(*first, *second));
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

t_dirs *dir_handler(char **args, int num_args, t_flags flags) {
  int i;
  t_dirs *dirs;

  i = -1;
  dirs = new_dir(".", IS_DIR, 1);
  if (!(flags & NEWEST_FIRST_SORT_FLAG))
    qsort(args, num_args, sizeof(char *), &dir_cmp);
  while (args[++i])
      set_dir(args[i], &dirs);
  if (flags & NEWEST_FIRST_SORT_FLAG)
    dir_sort(&dirs);
  return (dirs);
}
