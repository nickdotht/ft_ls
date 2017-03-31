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

t_format get_nondir_format(t_dirs **dirs, t_flags flags)
{
  t_format format;
  t_dirs *tmp;

  tmp = *dirs;
  format.date_month = 3;
  format.date_day = 2;
  format.date_hour = 2;
  format.date_minute = 2;
  format.date_year = 5;
  while (tmp)
  {
    if (tmp->status == IS_NOTDIR)
    {
      add_file(&tmp->self, &tmp, flags);
      format_handler(&format, tmp->self);
    }
    break;
    tmp = tmp->next;
  }
  return (format);
}