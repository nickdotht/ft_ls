#include "ft_ls.h"

t_dirs *new_dir(char *name, int status, int is_default, t_dirs *tail)
{
  t_dirs *dir;

  MEMCHECK((dir = (t_dirs *)ft_memalloc(sizeof(*dir))));
  MEMCHECK((dir->name = ft_strdup(name)));
  dir->format.date_month = 3;
  dir->format.date_day = 2;
  dir->format.date_hour = 2;
  dir->format.date_minute = 2;
  dir->status = status;
  dir->prev = tail;
  dir->next = NULL;
  dir->date.unix_format = get_dir_date(dir->name);
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

t_dirs *set_dir(char *arg, t_dirs **dirs, t_dirs *tail) {
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
  new = new_dir(arg, status, 0, tail);
  if (!*dirs || (*dirs)->is_default)
    *dirs = new;
  else
    add_dir(dirs, new);
  return (*dirs);
}

t_dirs *dir_handler(char **args, int num_args, t_flags flags) {
  int i;
  t_dirs *dirs;
  t_dirs *tail;

  i = -1;
  dirs = new_dir(".", IS_DIR, 1, NULL);
  if (!(flags & NEWEST_FIRST_SORT_FLAG))
    qsort(args, num_args, sizeof(char *), &dir_cmp);
  tail = NULL;
  while (args[++i])
      tail = set_dir(args[i], &dirs, tail);
  if (flags & NEWEST_FIRST_SORT_FLAG)
    dir_sort(&dirs);
  return (dirs);
}
