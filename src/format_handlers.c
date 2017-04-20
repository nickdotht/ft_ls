/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:11:17 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 21:00:50 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	initialize_format(t_format *format)
{
	format->date_month = 3;
	format->date_day = 2;
	format->date_hour = 2;
	format->date_minute = 2;
	format->date_year = 5;
	format->link = 0;
	format->owner = 0;
	format->group = 0;
	format->file_size = 0;
	format->user_id = 0;
	format->group_id = 0;
	format->major = 0;
	format->minor = 0;
}

void	format_handler(t_format *format, t_files *file, int format_option)
{
	if (format_option == IDLE_FORMAT)
		return ;
	if (format_option == INIT_FORMAT)
		initialize_format(format);
	if (format->link < ft_intlen(file->f.st_nlink))
		format->link = ft_intlen(file->f.st_nlink);
	if (format->owner < (int)ft_strlen(file->owner))
		format->owner = (int)ft_strlen(file->owner);
	if (format->group < (int)ft_strlen(file->group))
		format->group = (int)ft_strlen(file->group);
	if (format->file_size < ft_intlen(file->f.st_size))
		format->file_size = ft_intlen(file->f.st_size);
	if (format->user_id < ft_intlen((int)file->f.st_uid))
		format->user_id = ft_intlen((int)file->f.st_uid);
	if (format->group_id < ft_intlen((int)file->f.st_gid))
		format->group_id = ft_intlen((int)file->f.st_gid);
	if (format->major < ft_intlen((long)major(file->f.st_rdev)))
		format->major = ft_intlen((long)major(file->f.st_rdev));
	if (format->minor < ft_intlen((long)minor(file->f.st_rdev)))
		format->minor = ft_intlen((long)minor(file->f.st_rdev));
}
