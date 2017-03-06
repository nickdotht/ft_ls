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

int is_only_dir(t_dirs *head)
{
  t_dirs *tmp;
  int count;

  tmp = head;
  count = 0;
  while (tmp)
  {
      count++;
      tmp = tmp->next;
  }
  return (count > 1 ? 0 : 1);
}
