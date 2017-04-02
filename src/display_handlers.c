#include "ft_ls.h"

void date_display_handler(t_format format, t_date date)
{
  struct timeval tp;
  unsigned long long curr_date;
  unsigned long long six_months;

  gettimeofday(&tp, NULL);
  curr_date = (unsigned long long)tp.tv_sec;
  six_months = 15778476;
  if (date.tv_sec < (curr_date - six_months) || date.tv_sec > (curr_date + six_months))
    printf("%*s ", format.date_year, date.year);
  else
  {
    printf("%*s:", format.date_hour, date.hour);
    printf("%*s ", format.date_minute, date.minute);
  }
}

void long_listing_display(t_format format, t_files *file, int has_chr_or_blk, t_flags flags) {
  printf("%s ", file->modes);
  printf("%*ld ", format.link, file->link);
  if (file->owner && !(flags & DISPLAY_UID_AND_GID))
    printf("%-*s  ", format.owner, file->owner);
  else
    printf("%-*d  ", format.user_id, file->user_id);
  if (file->group && !(flags & DISPLAY_UID_AND_GID))
    printf("%-*s  ", format.group, file->group);
  else
    printf("%-*d  ", format.group_id, file->group_id);
  if (file->is_chr_or_blk)
    printf(" %*ld, %*ld ", format.major, file->major, format.minor, file->minor);
  else
    printf("%*ld ", has_chr_or_blk ? format.major + format.minor + format.fileSize + 2 : format.fileSize, file->size);
  printf("%*s ", format.date_month, file->date.month);
  printf("%*s ", format.date_day, file->date.day);
  date_display_handler(format, file->date);
  printf("%s", file->name);
  if (file->is_link)
    printf(" -> %s", file->linked_to);
  printf("\n");
}

void column_display(t_dirs *dirs, int target)
{
    struct winsize w;
    int cols;
    int rows;
    int num;
    int max_len;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
}

void nondir_display(t_dirs *dirs, t_flags flags) {
  t_dirs *tmp;
  int should_separate;
  t_format nondir_format;

  tmp = dirs;
  should_separate = has_dirs(dirs);
  nondir_format = get_nondir_format(&dirs, flags);
  if (!(flags & LONG_LISTING_FLAG))
    return (column_display(dirs, IS_NOTDIR));
  while (tmp)
  {
    if (tmp->status == IS_NOTDIR)
    {
      long_listing_display(nondir_format, tmp->self, tmp->has_chr_or_blk, flags);
      if (is_last_nondir(tmp) && should_separate)
        printf("\n");
    }
    tmp = tmp->next;
  }
}

void dir_display(t_dirs *dirs, t_flags flags) {
  if (!dirs->is_unreadable)
  {
    printf("total %d\n", dirs->total_blocks);
    while (dirs->files)
    {
      long_listing_display(dirs->format, dirs->files, dirs->has_chr_or_blk, flags);
      dirs->files = dirs->files->next;
    }
  }
  else
    printf("ft_ls: %s: Permission denied\n", dirs->name);
}

void display_handler(t_dirs *dirs, t_flags flags, int target) {
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
        memory_handler(etarget.file, ERROR_MEM);
      }
      tmp = tmp->next;
    }
  }
  else if (target == IS_NOTDIR)
      nondir_display(dirs, flags);
  else
    dir_display(dirs, flags);
}// if (!(flags & LONG_LISTING_FLAG))
//   return column_display(dirs, flags, target);


void ft_display(t_dirs *dirs, t_flags flags)
{
  t_dirs *tmp;

  display_handler(dirs, flags, IS_NONEXISTENT);
  display_handler(dirs, flags, IS_NOTDIR);
  tmp = dirs;
  while (tmp)
  {
    if (tmp->status == IS_DIR)
    {
      tmp->files = file_handler(tmp, flags);
      if (flags & REVERSE_FLAG)
        reverse_files(&tmp->files);
      if (dirs->next)
        printf("%s:\n", tmp->name);
      if (!(flags & LONG_LISTING_FLAG))
        column_display(tmp, IS_DIR);
      else
        display_handler(tmp, flags, IS_DIR);
      tmp->next = subdir_handler(tmp->next, &(tmp->sub_dirs), flags);
      if (!is_last_dir(tmp))
        printf("\n");
    }
    tmp = tmp->next;
  }
}