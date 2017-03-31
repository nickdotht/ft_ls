#include "ft_ls.h"

void format_handler(t_format *format, t_files *file) {
  if (format->link < ft_intlen(file->link))
    format->link = ft_intlen(file->link);
  if (format->owner < (int)ft_strlen(file->owner))
    format->owner = (int)ft_strlen(file->owner);
  if (format->group < (int)ft_strlen(file->group))
    format->group = (int)ft_strlen(file->group);
  if (format->fileSize < ft_intlen(file->size))
    format->fileSize = ft_intlen(file->size);
  if (format->user_id < ft_intlen(file->user_id))
    format->user_id = ft_intlen(file->user_id);
  if (format->group_id < ft_intlen(file->group_id))
    format->group_id = ft_intlen(file->group_id);
  if (format->major < ft_intlen(file->major))
    format->major = ft_intlen(file->major);
  if (format->minor < ft_intlen(file->minor))
    format->minor = ft_intlen(file->minor);
}
