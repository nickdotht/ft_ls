#include "ft_ls.h"

t_dirs *new_dir(char *name, t_status status) {
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
// 
// void sort_dirs(t_dirs **dirs) {
//
// }

void set_dir(char *arg, t_dirs **dirs) {
  t_dirs *new;
  t_status status;
  struct stat s;

  status = IS_DIR;
  if (stat(arg, &s) == -1) {
    if (ENOENT == errno)
      status = IS_NONEXISTENT;
  } else {
    if (!S_ISDIR(s.st_mode))
      status = IS_NOTDIR;
  }
  new = new_dir(arg, status);
  if (!*dirs)
    *dirs = new;
  else
    add_dir(dirs, new);
}

void dir_handler(char **args, t_flags flags) {
  int i;
  t_dirs *dirs;

  i = -1;
  dirs = NULL;
  while (args[++i])
    if (args[i][0] != '-')
      set_dir(args[i], &dirs);
  // sort_dirs(&dirs);
  display_handler(dirs, flags, IS_NONEXISTENT);
  display_handler(dirs, flags, IS_NOTDIR);
  while (dirs) {
    if (dirs->status & IS_DIR) {
      dirs->files = file_handler(dirs, flags);
      display_handler(dirs, flags, IS_DIR);
      if (dirs->next /*  && !is_last_dir(dirs) */)
        printf("\n");
    }
    dirs = dirs->next;
  }
}
