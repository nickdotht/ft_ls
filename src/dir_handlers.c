#include "ft_ls.h"

t_dirs *new_dir(char *name, t_status status, int is_default) {
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
  new = new_dir(arg, status, 0);
  if (!*dirs || (*dirs)->is_default) {
    *dirs = new;
  }
  else {
    add_dir(dirs, new);
  }
}

void dir_handler(char **args, int num_args, t_flags flags) {
  int i;
  t_dirs *dirs;
  t_dirs *head;

  i = -1;
  dirs = new_dir(".", IS_DIR, 1);
  qsort(args, num_args, sizeof(char *), &dir_cmp);
  while (args[++i])
      set_dir(args[i], &dirs);
  head = dirs;
  display_handler(NULL, dirs, flags, IS_NONEXISTENT);
  display_handler(NULL, dirs, flags, IS_NOTDIR);
  while (dirs) {
    if ((dirs->status & IS_DIR) == IS_DIR) {
      dirs->files = file_handler(dirs, flags);
      // printf("ABOUT TO START\n");
      while (dirs->sub_dirs)
      {
        printf("%s\n", dirs->sub_dirs->name);
        dirs->sub_dirs = dirs->sub_dirs->next;
      }
      exit(1);
      display_handler(head, dirs, flags, IS_DIR);
      if (!is_last_dir(dirs))
        printf("\n");
    }
    dirs = dirs->next;
  }
}
