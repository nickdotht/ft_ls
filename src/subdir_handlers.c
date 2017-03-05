#include "ft_ls.h"

t_dirs *subdir_handler(t_dirs *dirs)
{
  t_dirs *tmp;

  if (!dirs->sub_dirs) {
    return dirs->next;
  }
  tmp = dirs->sub_dirs;
  while (tmp->next) {
    tmp = tmp->next;
  }
  tmp->next = dirs->next;
  return (dirs->sub_dirs);
}
