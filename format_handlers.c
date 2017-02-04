#include "ft_ls.h"

int size_format(char *target_dir) {
  struct dirent *sd;
  DIR *dir;
  int longest;
  struct stat fileStat;

  longest = 0;
  if (!(dir = opendir(target_dir))) {
    printf("ls: cannot access '%s': No such file or directory\n", target_dir);
    return (0);
  }
  while ((sd = readdir(dir))) {
    if (stat(ft_pathjoin(target_dir, sd->d_name), &fileStat) < 0)
      return (0);
    if (longest < ft_intlength(fileStat.st_size))
      longest = ft_intlength(fileStat.st_size);
  }
  closedir(dir);
  return (longest);
}

int link_format(char *target_dir) {
  struct dirent *sd;
  DIR *dir;
  int longest;
  struct stat fileStat;

  longest = 0;
  if (!(dir = opendir(target_dir))) {
    printf("ls: cannot access '%s': No such file or directory\n", target_dir);
    return (0);
  }
  while ((sd = readdir(dir))) {
    if (stat(ft_pathjoin(target_dir, sd->d_name), &fileStat) < 0)
      return (0);
    if (longest < ft_intlength(fileStat.st_nlink)) {
      longest = ft_intlength(fileStat.st_nlink);
    }
  }
  closedir(dir);
  return (longest);
}

// void format_handler(t_format *format, t_dirs *dirs) {
//   t_format tmp;
//
//   tmp.fileSize = size_format(target_dir);
//   tmp.link = link_format(target_dir);
//   return (tmp);
// }
