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
    ft_memdel((void *)files);
    *files = next;
  }
}

void free_subdirs(t_dirs **subdirs)
{
  t_dirs *next;

  while (*subdirs)
  {
    next = (*subdirs)->next;
    free((*subdirs)->name);
    ft_memdel((void *)subdirs);
    *subdirs = next;
  }
}

void free_dirs(t_dirs **dirs)
{
  t_dirs *next;

  while (*dirs)
  {
    next = (*dirs)->next;
    free((*dirs)->name);
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
  else if (target == SUBDIRS_MEM)
    free_subdirs((t_dirs **)mem_target);
  else if (target == FILES_MEM)
    free_files((t_files **)mem_target);
}
