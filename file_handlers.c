#include "ft_ls.h"

char *formatdate(char *buff, time_t val) {
  strftime(buff, 200, "%b %d %H:%M", localtime(&val));
  return buff;
}

void add_file(t_dirs **dirs, char *file_name, t_flags flags) {
  char buff[200];
  struct stat f;

  if (stat(ft_pathjoin((*dirs)->name, file_name), &f) < 0)
    return;
  if (!((*dirs)->files->modes = ft_strnew(10)))
    return;
  (*dirs)->files->modes[0] = (S_ISDIR(f.st_mode)) ? 'd' : '-';
  (*dirs)->files->modes[1] = (f.st_mode & S_IRUSR) ? 'r' : '-';
  (*dirs)->files->modes[2] = (f.st_mode & S_IWUSR) ? 'w' : '-';
  (*dirs)->files->modes[3] = (f.st_mode & S_IXUSR) ? 'x' : '-';
  (*dirs)->files->modes[4] = (f.st_mode & S_IRGRP) ? 'r' : '-';
  (*dirs)->files->modes[5] = (f.st_mode & S_IWGRP) ? 'w' : '-';
  (*dirs)->files->modes[6] = (f.st_mode & S_IXGRP) ? 'x' : '-';
  (*dirs)->files->modes[7] = (f.st_mode & S_IROTH) ? 'r' : '-';
  (*dirs)->files->modes[8] = (f.st_mode & S_IWOTH) ? 'w' : '-';
  (*dirs)->files->modes[9] = (f.st_mode & S_IXOTH) ? 'x' : '-';
  (*dirs)->files->link = f.st_nlink;
  (*dirs)->files->owner = ft_strdup(getpwuid(f.st_uid)->pw_name);
  (*dirs)->files->group = ft_strdup(getgrgid(f.st_gid)->gr_name);
  (*dirs)->files->size = f.st_size;
  (*dirs)->files->date = ft_strdup(formatdate(buff, f.st_mtime));
  (*dirs)->files->name = ft_strdup(file_name);
  if (S_ISDIR(f.st_mode) && (flags & RECURSIVE_FLAG))
    set_dir(ft_pathjoin((*dirs)->name, file_name), dirs);
  (*dirs)->files->next = NULL;
}

// I should probably pass the address of the dir files 'cause I think every time
// I do it the way below, I always modify the first one
void file_handler(t_dirs **dirs, t_flags flags) {
  DIR *dir;
  struct dirent *sd;
  t_files *head_file;

  dir = opendir((*dirs)->name);
  head_file = (*dirs)->files;
  while ((sd = readdir(dir))) {
    if (!(flags & ALL_FLAG) && ft_strstartswith(sd->d_name, "."))
      continue;
    if (!((*dirs)->files = (t_files *)malloc(sizeof(t_files))))
      return;
    add_file(dirs, sd->d_name, flags);
    (*dirs)->files = (*dirs)->files->next;
  }
  (*dirs)->files = head_file;
  closedir(dir);
}
