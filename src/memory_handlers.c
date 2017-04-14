#include "ft_ls.h"

void free_files(t_files **files)
{
  t_files *next;

  while (*files)
  {
    next = (*files)->next;
    free((*files)->name);
    free((*files)->owner);
    free((*files)->group);
    free((*files)->modes);
    free((*files)->date.month);
    free((*files)->date.day);
    free((*files)->date.hour);
    free((*files)->date.minute);
    free((*files)->date.year);
    if ((*files)->has_nonprintable_chars)
      free((*files)->display_name);
    ft_memdel((void *)files);
    *files = next;
  }
}

void free_dirs(t_dirs **dirs)
{
  t_dirs *next;

  while (*dirs)
  {
    next = (*dirs)->next;
    free((*dirs)->name);
    free((*dirs)->display_name);
    free_files(&((*dirs)->files));
    free_files(&((*dirs)->self));
    ft_memdel((void *)dirs);
    *dirs = next;
  }
}


void memory_handler(void *mem_target, int target)
{
  if (target == DIRS_MEM)
    free_dirs((t_dirs **)mem_target);
  else if (target == ERROR_MEM)
    free(mem_target);
}
