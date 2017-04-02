#include "ft_ls.h"

void initialize_format(t_format *format)
{
  format->date_month = 3;
  format->date_day = 2;
  format->date_hour = 2;
  format->date_minute = 2;
  format->date_year = 5;
  format->link = 0;
  format->owner = 0;
  format->group = 0;
  format->fileSize = 0;
  format->user_id = 0;
  format->group_id = 0;
  format->major = 0;
  format->minor = 0;
}

void format_handler(t_format *format, t_files *file, int format_option) {
  if (format_option == INIT_FORMAT)
    initialize_format(format);
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
