#include "ft_ls.h"

void date_display_handler(t_format format, t_date date, t_flags flags)
{
  struct timeval tp;
  unsigned long long curr_date;
  unsigned long long six_months;
  unsigned long long t;

  gettimeofday(&tp, NULL);
  curr_date = (unsigned long long)tp.tv_sec;
  six_months = 15778476;
  t = date.mtv_sec;
  if (flags & CREATION_DATE_SORT)
    t = date.birthtv_sec;
  if (flags & LAST_ACCESS_DATE_SORT)
    t = date.atv_sec;
  if (flags & LAST_STATUS_CHANGE_SORT)
    t = date.ctv_sec;
  if (t < (curr_date - six_months) || t > (curr_date + six_months))
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
  if (!(flags & SUPRESS_OWNER))
  {
    if (file->owner && !(flags & DISPLAY_UID_AND_GID))
      printf("%-*s  ", format.owner, file->owner);
    else
      printf("%-*d  ", format.user_id, file->user_id);
  }
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
  date_display_handler(format, file->date, flags);
  if (file->has_unprintable_chars)
    printf("%s", file->display_name);
  else
    printf("%s", file->name);
  if (file->is_link)
    printf(" -> %s", file->linked_to);
  printf("\n");
}

void column_display(t_entries entries, int file_count, int max_file_len, int target)
{
    struct winsize w;
    int cols;
    int rows;
    char **arr;
    int term_width;
    int i;
    int pos;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    term_width = w.ws_col;
    cols = term_width / (max_file_len + 1);
    if ((max_file_len + 1) * file_count < term_width)
      cols = file_count;
    rows = file_count / cols;
    if (file_count % cols)
      ++rows;
    arr = NULL;
    if (target == IS_DIR)
    {
      MEMCHECK((arr = (char **)ft_memalloc(sizeof(char *) * (file_count + 1))));
      i = 0;
      while (entries.files)
      {
        if (entries.files->has_unprintable_chars)
          arr[i++] = ft_strdup(entries.files->display_name);
        else
          arr[i++] = ft_strdup(entries.files->name);
        entries.files = entries.files->next;
      }
    }
    pos = 0;
    i = -1;
    while (++i < rows)
    {
      int j = -1;
      pos = i;
      while (++j < cols)
      {
        printf("%-*s ", max_file_len, target == IS_DIR ? arr[pos] : entries.file_names[pos]);
        pos += rows;
        if (pos >= file_count)
          break;
      }
      printf("\n");
    }
    if (target == IS_DIR)
      free(arr);
}

void nondir_column_display(t_dirs *dirs, int should_separate)
{
  t_dirs *tmp;
  int file_count;
  t_entries entries;
  int max_file_len;
  int i;

  file_count = 0;
  max_file_len = 0;
  tmp = dirs;
  while (tmp)
  {
    if (tmp->status == IS_NOTDIR)
    {
      ++file_count;
      if ((int)ft_strlen(tmp->self->name) > max_file_len)
        max_file_len = ft_strlen(tmp->self->name);
    }
    tmp = tmp->next;
  }
  MEMCHECK((entries.file_names = (char **)ft_memalloc(sizeof(char *) * file_count)));
  tmp = dirs;
  i = -1;
  while (tmp)
  {
    if (tmp->status == IS_NOTDIR)
    {
      if (tmp->self->has_unprintable_chars)
        entries.file_names[++i] = ft_strdup(tmp->self->display_name);
      else
        entries.file_names[++i] = ft_strdup(tmp->self->name);
    }
    tmp = tmp->next;
  }
  if (file_count)
    column_display(entries, file_count, max_file_len, IS_NOTDIR);
  free(entries.file_names);
  if (file_count && should_separate)
    printf("\n");
}

void nondir_display(t_dirs *dirs, t_flags flags) {
  t_dirs *tmp;
  int should_separate;
  t_format nondir_format;

  should_separate = has_dirs(dirs);
  if (flags & COLUMN_DISPLAY)
    return (nondir_column_display(dirs, should_separate));
  nondir_format = get_nondir_format(&dirs, flags);
  tmp = dirs;
  while (tmp)
  {
    if (tmp->status == IS_NOTDIR)
    {
      if (flags & LONG_LISTING_FLAG)
        long_listing_display(nondir_format, tmp->self, tmp->has_chr_or_blk, flags);
      else
      {
        if (tmp->self->has_unprintable_chars)
          printf("%s\n", tmp->self->display_name);
        else
          printf("%s\n", tmp->self->name);
      }
      if (is_last_nondir(tmp) && should_separate)
        printf("\n");
    }
    tmp = tmp->next;
  }
}

void dir_display(t_dirs *head, t_dirs *dirs, t_flags flags) {
  t_entries entries;

  if (head->next)
      printf("%s:\n", dirs->name);
  if (dirs->is_unreadable)
    return ((void)printf("ft_ls: %s: Permission denied\n", dirs->name));
  if (flags & LONG_LISTING_FLAG)
    printf("total %d\n", dirs->total_blocks);
  else if (flags & COLUMN_DISPLAY)
  {
    entries.files = dirs->files;
    if (dirs->file_count)
      return (column_display(entries, dirs->file_count, dirs->max_file_len, IS_DIR));
  }
  while (dirs->files)
  {
    if (flags & LONG_LISTING_FLAG)
      long_listing_display(dirs->format, dirs->files, dirs->has_chr_or_blk, flags);
    else
    {
      if (dirs->files->has_unprintable_chars)
        printf("%s\n", dirs->files->display_name);
      else
        printf("%s\n", dirs->files->name);
    }
    dirs->files = dirs->files->next;
  }
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
        memory_handler(etarget.file, ERROR_MEM);
      }
      tmp = tmp->next;
    }
  }
  else if (target == IS_NOTDIR)
      nondir_display(dirs, flags);
  else
    dir_display(head, dirs, flags);
}

void ft_display(t_dirs *dirs, t_flags flags)
{
  t_dirs *tmp;

  display_handler(NULL, dirs, flags, IS_NONEXISTENT);
  display_handler(NULL, dirs, flags, IS_NOTDIR);
  tmp = dirs;
  while (tmp)
  {
    if (tmp->status == IS_DIR)
    {
      tmp->files = file_handler(tmp, flags);
      if (flags & REVERSE_FLAG)
        reverse_files(&tmp->files);
      display_handler(dirs, tmp, flags, IS_DIR);
      tmp->next = subdir_handler(tmp->next, &(tmp->sub_dirs), flags);
      if (!is_last_dir(tmp))
        printf("\n");
    }
    tmp = tmp->next;
  }
}