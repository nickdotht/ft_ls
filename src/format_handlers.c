#include "ft_ls.h"

void format_handler(t_dirs **dir, t_files *file) {
  if ((*dir)->format.link < ft_intlen(file->link))
    (*dir)->format.link = ft_intlen(file->link);
  if ((*dir)->format.owner < (int)ft_strlen(file->owner))
    (*dir)->format.owner = (int)ft_strlen(file->owner);
  if ((*dir)->format.group < (int)ft_strlen(file->group))
    (*dir)->format.group = (int)ft_strlen(file->group);
  if ((*dir)->format.fileSize < ft_intlen(file->size))
    (*dir)->format.fileSize = ft_intlen(file->size);
  if ((*dir)->format.user_id < ft_intlen(file->user_id))
    (*dir)->format.user_id = ft_intlen(file->user_id);
  if ((*dir)->format.group_id < ft_intlen(file->group_id))
    (*dir)->format.group_id = ft_intlen(file->group_id);
  if ((*dir)->format.major < ft_intlen(file->major))
    (*dir)->format.major = ft_intlen(file->major);
  if ((*dir)->format.minor < ft_intlen(file->minor))
    (*dir)->format.minor = ft_intlen(file->minor);
}
