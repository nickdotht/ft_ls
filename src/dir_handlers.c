#include "ft_ls.h"

t_dirs *new_dir(char *name, int status, int is_default) {
  t_dirs *dir;

  if (!(dir = (t_dirs *)malloc(sizeof(*dir))))
    return (NULL);
  if (!(dir->name = ft_strdup(name)))
    return (NULL);
  dir->status = status;
  dir->format.link = 0;
  dir->format.owner = 0;
  dir->format.group = 0;
  dir->format.fileSize = 0;
  dir->format.date_month = 3;
  dir->format.date_day = 2;
  dir->format.date_hour = 2;
  dir->format.date_minute = 2;
  dir->next = NULL;
  dir->is_default = is_default;
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
    return (strcmp(*first, *second));
}

void set_dir(char *arg, t_dirs **dirs) {
  t_dirs *new;
  int status;
  struct stat s;

  status = IS_DIR;
  if (stat(arg, &s) == -1) {
    if (ENOENT == errno)
      status = IS_NONEXISTENT;
  } else {
    if (!S_ISDIR(s.st_mode))
      status = IS_NOTDIR;
  }
  new = new_dir(arg, status, 0);
  if (!*dirs || (*dirs)->is_default) {
    *dirs = new;
  }
  else {
    add_dir(dirs, new);
  }
}

t_dirs *dir_handler(char **args, int num_args) {
  int i;
  t_dirs *dirs;

  i = -1;
  dirs = new_dir(".", IS_DIR, 1);
  qsort(args, num_args, sizeof(char *), &dir_cmp);
  while (args[++i])
      set_dir(args[i], &dirs);
  return (dirs);
}
