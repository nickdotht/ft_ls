#include "ft_ls.h"

void add_file(t_files **alst, t_files *new) {
  t_files *tmp;
  t_files *head;

  tmp = *alst;
  head = tmp;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
  *alst = head;
}

char *formatdate(char *buff, time_t val) {
  strftime(buff, 200, "%b %d %H:%M", localtime(&val));
  return buff;
}

void add_file(t_dirs **dirs, char **file_name, t_flags flags) {
  char buff[200];
  struct stat file;

  if (stat(ft_pathjoin((*dirs)->name, file), &file) < 0)
    return;
  if (!((*dirs)->files->modes = ft_strnew(10)))
    return;
  (*dirs)->files->modes[0] = (S_ISDIR(file.st_mode)) ? "d" : "-";
  (*dirs)->files->modes[1] = (file.st_mode & S_IRUSR) ? "r" : "-";
  (*dirs)->files->modes[2] = (file.st_mode & S_IWUSR) ? "w" : "-";
  (*dirs)->files->modes[3] = (file.st_mode & S_IXUSR) ? "x" : "-";
  (*dirs)->files->modes[4] = (file.st_mode & S_IRGRP) ? "r" : "-";
  (*dirs)->files->modes[5] = (file.st_mode & S_IWGRP) ? "w" : "-";
  (*dirs)->files->modes[6] = (file.st_mode & S_IXGRP) ? "x" : "-";
  (*dirs)->files->modes[7] = (file.st_mode & S_IROTH) ? "r" : "-";
  (*dirs)->files->modes[8] = (file.st_mode & S_IWOTH) ? "w" : "-";
  (*dirs)->files->modes[9] = (file.st_mode & S_IXOTH) ? "x" : "-";
  printf(" %*lu", ll_format.link, file.st_nlink);
  printf(" %s", getpwuid(file.st_uid)->pw_name);
  printf(" %s", getgrgid(file.st_gid)->gr_name);
  printf(" %*ld", ll_format.fileSize, file.st_size);
  printf(" %s", formatdate(buff, file.st_mtime));
  printf(" %s\n", file);
  if (S_ISDIR(file.st_mode))
    set_dir(ft_pathjoin((*dirs)->name, file_name), dirs, flags);

  /* printf("The file %s a symbolic link\n\n", (S_ISLNK(file.st_mode)) ? "is" :
   * "is not"); */
}

void file_handler(t_dirs **dirs, t_flags flags) {
  DIR *dir;
  struct dirent *sd;

  dir = opendir((*dirs)->name));
  while ((sd = readdir(dir))) {
    if (!((*dirs)->files = (t_files *)malloc(sizeof(*files))))
      return;
    if (!(flags & ALL_FLAG) && ft_strstartswith(sd->name, "."))
      continue;
    add_file(dirs, sd->name, flags);
    (*dirs)->files = (*dirs)->files->next;
  }
  closedir(dir);
}
