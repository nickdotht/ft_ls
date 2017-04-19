#include "ft_ls.h"

int is_last_dir(t_dirs *dirs)
{
  t_dirs *tmp;

  tmp = dirs->next;
  while (tmp)
  {
    if (tmp->status == IS_DIR)
      return (0);
    tmp = tmp->next;
  }
  return (1);
}

int is_last_nondir(t_dirs *dirs)
{
  t_dirs *tmp;

  tmp = dirs->next;
  while (tmp)
  {
    if (tmp->status == IS_NOTDIR)
      return (0);
    tmp = tmp->next;
  }
  return (1);
}

int has_dirs(t_dirs *dirs)
{
  t_dirs *tmp;

  tmp = dirs;
  while (tmp)
  {
    if (tmp->status == IS_DIR)
      return (1);
    tmp = tmp->next;
  }
  return (0);
}

t_format get_nondir_format(t_dirs **dirs)
{
  t_format format;
  t_dirs *tmp;
  int format_option;

  tmp = *dirs;
  format_option = INIT_FORMAT;
  while (tmp)
  {
    if (tmp->status == IS_NOTDIR)
    {
      add_file(&tmp->self, &tmp, INIT_FORMAT);
      if (g_flags & LONG_LISTING_FLAG)
        format_handler(&format, tmp->self, format_option);
      format_option = UPDATE_FORMAT;
    }
    tmp = tmp->next;
  }
  return (format);
}

void	date_initializer(t_date *date, struct stat f)
{
	date->mtv_sec = (unsigned long long)f.st_mtimespec.tv_sec;
	date->mtv_nsec = (unsigned long long)f.st_mtimespec.tv_nsec;
	date->atv_sec = (unsigned long long)f.st_atimespec.tv_sec;
	date->atv_nsec = (unsigned long long)f.st_atimespec.tv_nsec;
	date->ctv_sec = (unsigned long long)f.st_ctimespec.tv_sec;
	date->ctv_nsec = (unsigned long long)f.st_ctimespec.tv_nsec;
	date->birthtv_sec = (unsigned long long)f.st_birthtimespec.tv_sec;
	date->birthtv_nsec = (unsigned long long)f.st_birthtimespec.tv_nsec;
}