#include "ft_ls.h"

void long_listing_display(t_format format, t_files *file) {
  printf("%s ", file->modes);
  printf("%*ld ", format.link, file->link);
  printf("%*s  ", format.owner, file->owner);
  printf("%*s  ", format.group, file->group);
  printf("%*ld ", format.fileSize, file->size);
  printf("%*s ", format.date_month, file->date.month);
  printf("%*s ", format.date_day, file->date.day);
  printf("%*s:", format.date_hour, file->date.hour);
  printf("%*s ", format.date_minute, file->date.minute);
  printf("%s\n", file->name);
}

// void column_display(t_dirs *dirs, t_flags flags, t_status target) {
//   // Will work on this later.
// }
void nondir_display(t_dirs *dirs, t_flags flags) {
  t_dirs *tmp;
  int should_separate;

  tmp = dirs;
  should_separate = has_dirs(dirs);
  while (tmp)
  {
    if (tmp->status == IS_NOTDIR)
    {
      add_file(&tmp->self, &tmp, flags);
      long_listing_display(dirs->format, tmp->self);
      if (is_last_nondir(tmp) && should_separate)
        printf("\n");
    }
    tmp = tmp->next;
  }
}

void ft_display(t_dirs *dirs, t_dirs *head, t_flags flags)
{
  display_handler(NULL, dirs, flags, IS_NONEXISTENT);
  display_handler(NULL, dirs, flags, IS_NOTDIR);
  while (dirs)
  {
    if (dirs->status == IS_DIR)
    {
      dirs->files = file_handler(dirs, flags);
      if (flags & REVERSE_FLAG)
        reverse_files(&dirs->files);
      display_handler(head, dirs, flags, IS_DIR);
      dirs->next = subdir_handler(dirs->next, &(dirs->sub_dirs), flags);
      if (!is_last_dir(dirs))
        printf("\n");
    }
    dirs = dirs->next;
  }
}

void dir_display(t_dirs *head, t_dirs *dirs) {
  if (head->next)
    printf("%s:\n", dirs->name);
  if (!dirs->is_unreadable)
  {
    printf("total %d\n", dirs->total_blocks);
    while (dirs->files)
    {
      long_listing_display(dirs->format, dirs->files);
      dirs->files = dirs->files->next;
    }
  }
  else
    printf("ft_ls: %s: Permission denied\n", dirs->name);
}

void display_handler(t_dirs *head, t_dirs *dirs, t_flags flags, int target) {
  t_etarget etarget;
  t_dirs  *tmp;

  if (target == IS_NONEXISTENT)
  {
    tmp = dirs;
    while (tmp) {
      if (tmp->status == IS_NONEXISTENT)
      {
        MEMCHECK((etarget.file = ft_strdup(tmp->name)));
        error_handler(NONEXISTENT_ERR, etarget);
      }
      tmp = tmp->next;
    }
  }
  else if (target == IS_NOTDIR)
      nondir_display(dirs, flags);
  else
    dir_display(head, dirs);
}// if (!(flags & LONG_LISTING_FLAG))
//   return column_display(dirs, flags, target);
