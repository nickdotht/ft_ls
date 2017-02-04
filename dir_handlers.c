#include "ft_ls.h"

t_dirs *new_dir(char *name, t_status status) {
  t_dirs *dir;

  if (!(dir = (t_dirs *)malloc(sizeof(*dir))))
    return (NULL);
  if (!(dir->name = ft_strdup(name)))
    return (NULL);
  dir->status = status;
  dir->next = NULL;
  return (dir);
}

void add_dir(t_dirs **alst, t_dirs *new) {
  t_dirs *tmp;
  t_dirs *head;

  tmp = *alst;
  head = tmp;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
  *alst = head;
}

// void sort_dirs(t_dirs **dirs) {
//
// }

void set_dir(char *arg, t_dirs **dirs, t_flags flags) {
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
  if (!(*dirs)->name) {
    *dirs = new_dir(arg, status);
    return;
  }
  new = new_dir(arg, status);
  add_dir(dirs, new);
}

void dir_handler(char **args, t_flag flags) {
  int i;
  t_dirs *dirs;

  if (!(dirs = (t_dirs *)malloc(sizeof(*dirs))))
    return (0);
  i = -1;
  while (args[++i])
    if (args[i][0] != '-')
      set_dir(args[i], &dirs, flags);
  // sort_dirs(&dirs);
  while (dirs) {
    file_handler(dirs, flags);
    display_handler(dirs, flags);
    if (dirs->next)
      printf("\n");
    dirs = dirs->next;
  }
}
