// #include "ft_ls.h"
//
// void free_dirs(t_dirs **dirs)
// {
//   while ((*dirs))
//   {
//     next = (*dirs)->next;
//     free((*dirs)->name);
//     ft_memdel((void *)dirs);
//     (*dirs) = next;
//   }
// }
//
// void memory_handler(void *target, int target)
// {
//   if (target == DIRS_MEM || target == SUBDIRS_MEM)
//     free_dirs((t_dirs **)target);
//   else if (target == FILES_MEM)
//     free_files((t_files **)target);
// }
