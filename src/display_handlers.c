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
  if (t <= (curr_date - six_months) || t >= (curr_date + six_months))
    print_handler(1, "%s ", format.date_year, date.year);
  else
  {
    print_handler(1, "%s:", format.date_hour, date.hour);
    print_handler(1, "%s ", format.date_minute, date.minute);
  }
}

void display_file_name(struct stat f, char *name, t_flags flags)
{
  if (!(flags & COLORED_OUTPUT))
    return (print_handler(1, "%s", 0, name));
  if (S_ISDIR(f.st_mode))
    print_handler(1, ANSI_COLOR_BOLD_CYAN "%s" ANSI_COLOR_RESET, 0, name);
  else if (S_ISLNK(f.st_mode))
    print_handler(1, ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET, 0, name);
  else if (S_ISSOCK(f.st_mode))
    print_handler(1, ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, 0, name);
  else if (S_ISFIFO(f.st_mode))
    print_handler(1, ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, 0, name);
  else if (S_ISBLK(f.st_mode))
    print_handler(1, ANSI_COLOR_BOLD_GREEN "%s" ANSI_COLOR_RESET, 0, name);
  else if (S_ISCHR(f.st_mode))
    print_handler(1, ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, 0, name);
  else if (S_ISREG(f.st_mode) && f.st_mode & S_IXUSR)
    print_handler(1, ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, 0, name);
  else
    print_handler(1, "%s", 0, name);
}

void long_listing_display(t_format format, t_files *file, int has_chr_or_blk, t_flags flags) {
  print_handler(1, "%s ", 0, file->modes);
  print_handler(1, "%ld ", format.link, ft_itoa(file->link));
  if (!(flags & SUPRESS_OWNER))
  {
    if (file->owner && !(flags & DISPLAY_UID_AND_GID))
      lprint_handler(1, "%s  ", format.owner, file->owner);
    else
      lprint_handler(1, "%d  ", format.user_id, ft_itoa(file->user_id));
  }
  if (file->group && !(flags & DISPLAY_UID_AND_GID))
    lprint_handler(1, "%s  ", format.group, file->group);
  else
    lprint_handler(1, "%d  ", format.group_id, ft_itoa(file->group_id));
  if (file->is_chr_or_blk)
  {
    print_handler(1, " %ld", format.major, ft_itoa(file->major));
    print_handler(1, "%ld ", format.minor, ft_itoa(file->minor));
  }
  else
    print_handler(1, "%ld ", has_chr_or_blk ? format.major + format.minor + format.fileSize + 2 : format.fileSize, ft_itoa(file->size));
  print_handler(1, "%s ", format.date_month, file->date.month);
  print_handler(1, "%s ", format.date_day, file->date.day);
  date_display_handler(format, file->date, flags);
  if (file->has_nonprintable_chars)
    display_file_name(file->f, file->display_name, flags);
  else
    display_file_name(file->f, file->name, flags);
  if (file->is_link)
    print_handler(1, " -> %s", 0, file->linked_to);
  print_handler(1, "\n", 0, NULL);
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
    if (!cols)
      cols = 1;
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
        if (entries.files->has_nonprintable_chars)
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
        lprint_handler(1, "%s ", max_file_len, target == IS_DIR ? arr[pos] : entries.file_names[pos]);
        pos += rows;
        if (pos >= file_count)
          break;
      }
      print_handler(1, "\n", 0, NULL);
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
      if (tmp->self->has_nonprintable_chars)
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
    print_handler(1, "\n", 0, NULL);
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
        if (tmp->self->has_nonprintable_chars)
          print_handler(1, "%s\n", 0, tmp->self->display_name);
        else
          print_handler(1, "%s\n", 0, tmp->self->name);
      }
      if (is_last_nondir(tmp) && should_separate)
        print_handler(1, "\n", 0, NULL);
    }
    tmp = tmp->next;
  }
}

void dir_display(t_dirs *head, t_dirs *dirs, t_flags flags) {
  t_entries entries;
  t_etarget target;

  if (head->next)
      print_handler(1, "%s:\n", 0, dirs->name);
  if (dirs->is_unreadable)
  {
    MEMCHECK((target.file = ft_strdup(dirs->display_name)));
    return (error_handler(FILE_ACCESS_ERR, target));
    free(target.file);
  }
  if ((flags & LONG_LISTING_FLAG) && dirs->files && dirs->has_valid_files)
    print_handler(1, "total %d\n", 0, ft_itoa(dirs->total_blocks));
  if (flags & COLUMN_DISPLAY)
  {
    entries.files = dirs->files;
    if (dirs->file_count)
      return (column_display(entries, dirs->file_count, dirs->max_file_len, IS_DIR));
  }
  while (dirs->files)
  {
    if (dirs->files->status == IS_NONEXISTENT) {
      if (dirs->files->has_nonprintable_chars) {
        MEMCHECK((target.file = ft_strdup(dirs->files->display_name)));
      }
      else {
        MEMCHECK((target.file = ft_strdup(dirs->files->name)));
      }
      error_handler(NONEXISTENT_ERR, target);
      free(target.file);
    }
    else if (dirs->files->status == IS_UNREADABLE) {
      if (dirs->files->has_nonprintable_chars) {
        MEMCHECK((target.file = ft_strdup(dirs->files->display_name)));
      }
      else {
        MEMCHECK((target.file = ft_strdup(dirs->files->name)));
      }
      error_handler(FILE_ACCESS_ERR, target);
      free(target.file);
    }
    else {
      if (flags & LONG_LISTING_FLAG)
        long_listing_display(dirs->format, dirs->files, dirs->has_chr_or_blk, flags);
      else
      {
        if (dirs->files->has_nonprintable_chars)
          print_handler(1, "%s\n", 0, dirs->files->display_name);
        else
          print_handler(1, "%s\n", 0, dirs->files->name);
      }
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
  if (flags & REVERSE_FLAG)
    reverse_dirs(&dirs);
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
        print_handler(1, "\n", 0, NULL);
    }
    tmp = tmp->next;
  }
}