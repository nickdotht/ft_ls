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
  if (*dirs == NULL) {
    *dirs = new_dir(arg, status);
    return;
  }
  new = new_dir(arg, status);
  add_dir(dirs, new);
}

void dir_handler(char **args, t_flags flags) {
  int i;
  t_dirs *dirs;

  if (!(dirs = (t_dirs *)malloc(sizeof(*dirs))))
    return;
  i = -1;
  while (args[++i])
    if (args[i][0] != '-')
      set_dir(args[i], &dirs);
  // sort_dirs(&dirs);
  display_handler(dirs, IS_NONEXISTENT);
  display_handler(dirs, IS_NOTDIR);
  while (dirs) {
    if (dirs->status & IS_DIR) {
      file_handler(&dirs, flags);
      display_handler(dirs, IS_DIR);
      if (dirs->next /*  && !is_last_dir(dirs) */)
        printf("\n");
    }
    dirs = dirs->next;
  }
}