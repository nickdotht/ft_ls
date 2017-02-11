#include "ft_ls.h"

void long_listing_display(t_files *file) {
  printf("%s ", file->modes);
  printf("%ld ", file->link);
  printf("%s ", file->owner);
  printf("%s ", file->group);
  printf("%ld ", file->size);
  printf("%s ", file->date);
  printf("%s\n", file->name);
}

// void column_display(t_dirs *dirs, t_flags flags, t_status target) {
//   // Will work on this later.
// }
void nondir_display(t_dirs *dirs, t_flags flags) {
  t_dirs *tmp;

  tmp = dirs;
  while (tmp)
  {
    if (tmp->status & IS_NOTDIR)
    {
      tmp->self = (t_files *)malloc(sizeof(t_files));
      add_file(&tmp->self, &tmp, NULL, tmp->name, flags);
      tmp->next = NULL;
      long_listing_display(tmp->self);
    }
    tmp = tmp->next;
  }
}

void dir_files_display(t_files *files) {
  while (files->next)
  {
    long_listing_display(files);
    files = files->next;
  }
}

void display_handler(t_dirs *dirs, t_flags flags, t_status target) {
  t_etarget etarget;
  t_dirs  *tmp;

  if (target & IS_NONEXISTENT) {
    tmp = dirs;
    while (tmp) {
      if (tmp->status & IS_NONEXISTENT) {
        if (!(etarget.file = ft_strdup(tmp->name)))
          return;
        error_handler(NONEXISTENT_ERR, etarget);
      }
      tmp = tmp->next;
    }
  }
  else if (target & IS_NOTDIR)
      nondir_display(dirs, flags);
  else
  {
    printf("%s:\n", dirs->name);
    dir_files_display(dirs->files);
  }
}// if (!(flags & LONG_LISTING_FLAG))
//   return column_display(dirs, flags, target);
