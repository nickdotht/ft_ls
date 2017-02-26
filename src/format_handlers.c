#include "ft_ls.h"

void format_handler(t_dirs **dir, struct stat file_stat) {
  if ((*dir)->format.link < ft_intlength(file_stat.st_nlink))
    (*dir)->format.link = ft_intlength(file_stat.st_nlink);
  if ((*dir)->format.owner < (int)ft_strlen(getpwuid(file_stat.st_uid)->pw_name))
    (*dir)->format.owner = ft_strlen(getpwuid(file_stat.st_uid)->pw_name);
  if ((*dir)->format.group < (int)ft_strlen(getgrgid(file_stat.st_gid)->gr_name))
    (*dir)->format.group = ft_strlen(getgrgid(file_stat.st_gid)->gr_name);
  if ((*dir)->format.fileSize < ft_intlength(file_stat.st_size))
    (*dir)->format.fileSize = ft_intlength(file_stat.st_size);
}
