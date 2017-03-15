#include "ft_ls.h"

void add_date(t_date *date, time_t val) {
  char buff[200];

  strftime(buff, 200, "%b", localtime(&val));
  MEMCHECK((date->month = ft_strdup(buff)));
  strftime(buff, 200, "%-d", localtime(&val));
  MEMCHECK((date->day = ft_strdup(buff)));
  strftime(buff, 200, "%H", localtime(&val));
  MEMCHECK((date->hour = ft_strdup(buff)));
  strftime(buff, 200, "%M", localtime(&val));
  MEMCHECK((date->minute = ft_strdup(buff)));
}

void add_file(t_files **curr_file, t_dirs **dirs, char *dir_name, char *file_name, t_flags flags) {
  struct stat f;

  if (lstat(!dir_name ? file_name : ft_pathjoin(dir_name, file_name), &f) < 0 ||
  !((*curr_file)->modes = ft_strnew(10)))
    exit(2);
  format_handler(dirs, f);
  (*curr_file)->modes[0] = (S_ISDIR(f.st_mode)) ? 'd' : '-';
  (*curr_file)->modes[1] = (f.st_mode & S_IRUSR) ? 'r' : '-';
  (*curr_file)->modes[2] = (f.st_mode & S_IWUSR) ? 'w' : '-';
  (*curr_file)->modes[3] = (f.st_mode & S_IXUSR) ? 'x' : '-';
  (*curr_file)->modes[4] = (f.st_mode & S_IRGRP) ? 'r' : '-';
  (*curr_file)->modes[5] = (f.st_mode & S_IWGRP) ? 'w' : '-';
  (*curr_file)->modes[6] = (f.st_mode & S_IXGRP) ? 'x' : '-';
  (*curr_file)->modes[7] = (f.st_mode & S_IROTH) ? 'r' : '-';
  (*curr_file)->modes[8] = (f.st_mode & S_IWOTH) ? 'w' : '-';
  (*curr_file)->modes[9] = (f.st_mode & S_IXOTH) ? 'x' : '-';
  (*curr_file)->link = f.st_nlink;
  (*curr_file)->owner = ft_strdup(getpwuid(f.st_uid)->pw_name);
  (*curr_file)->group = ft_strdup(getgrgid(f.st_gid)->gr_name);
  (*curr_file)->size = f.st_size;
  add_date(&(*curr_file)->date, f.st_mtime);
  MEMCHECK(((*curr_file)->name = ft_strdup(file_name)));
  if (S_ISDIR(f.st_mode) && (flags & RECURSIVE_FLAG))
    set_dir(ft_pathjoin(dir_name, file_name), &(*dirs)->sub_dirs);
}

t_files *file_handler(t_dirs *dirs, t_flags flags) {
  DIR   *dir;
  struct dirent *sd;
  t_files *files;
  t_files *tmp;

  if (!(dir = opendir(dirs->name)))
  {
    dirs->is_unreadable = 1;
    return (NULL);
  }
  MEMCHECK(((files = (t_files *)ft_memalloc(sizeof(t_files)))));
  tmp = files;
  while ((sd = readdir(dir)))
  {
    if (!(flags & ALL_FLAG) && sd->d_name[0] == '.')
      continue ;
    add_file(&tmp, &dirs, dirs->name, sd->d_name, flags);
    MEMCHECK((tmp->next = (t_files *)ft_memalloc(sizeof(t_files))));
    tmp = tmp->next;
  }
  tmp->next = NULL;
  closedir(dir);
  // file_sort(&head);
  return (files);
}
