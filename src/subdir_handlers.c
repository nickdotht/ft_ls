#include "ft_ls.h"

t_dirs *subdir_handler(t_dirs *next, t_dirs *sub_dirs)
{
  t_dirs *tmp;

  if (!sub_dirs) {
    return next;
  }
  tmp = sub_dirs;
  while (tmp->next) {
    tmp = tmp->next;
  }
  tmp->next = next;
  return (sub_dirs);
}
