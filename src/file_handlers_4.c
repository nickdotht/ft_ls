/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handlers_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:47:52 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 17:53:49 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	file_date_handler(t_date *date, struct stat f)
{
	char					buff[200];
	unsigned long long		t;

	date_initializer(date, f);
	t = date->mtv_sec;
	if (g_flags & CREATION_DATE_SORT)
		t = date->birthtv_sec;
	if (g_flags & LAST_ACCESS_DATE_SORT)
		t = date->atv_sec;
	if (g_flags & LAST_STATUS_CHANGE_SORT)
		t = date->ctv_sec;
	strftime(buff, 200, "%b", localtime((const long *)&t));
	MEMCHECK((date->month = ft_strdup(buff)));
	strftime(buff, 200, "%-d", localtime((const long *)&t));
	MEMCHECK((date->day = ft_strdup(buff)));
	strftime(buff, 200, "%H", localtime((const long *)&t));
	MEMCHECK((date->hour = ft_strdup(buff)));
	strftime(buff, 200, "%M", localtime((const long *)&t));
	MEMCHECK((date->minute = ft_strdup(buff)));
	strftime(buff, 200, "%Y", localtime((const long *)&t));
	MEMCHECK((date->year = ft_strdup(buff)));
}

char	extended_attributes_handler(char *file_path)
{
	char			res;
	acl_t			acl;
	acl_entry_t		entry;

	res = ' ';
	if (listxattr(file_path, NULL, 0, XATTR_NOFOLLOW) == -1)
	{
		if (errno == EPERM || errno == EACCES || errno == EFAULT)
			return (' ');
	}
	else if (listxattr(file_path, NULL, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	acl = acl_get_link_np(file_path, ACL_TYPE_EXTENDED);
	if (!acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (acl)
		res = '+';
	return (res);
}

char	*serialize_name(char *name, int len)
{
	char	*new;
	int		i;
	char	c;

	MEMCHECK((new = ft_strnew(ft_strlen(name))));
	i = -1;
	while (i < len && name[i])
	{
		c = name[i];
		if (IS_NONPRINTABLE(name[i]))
		{
			if (name[i] == '\r')
				c = '?';
			else
				c = ' ';
		}
		new[i] = c;
	}
	return (new);
}

int		has_nonprintable_chars(char *s, int len)
{
	int i;

	i = -1;
	while (++i < len && s[i])
		if (IS_NONPRINTABLE(s[i]))
			return (1);
	return (0);
}

void	file_permission_handler(t_files **curr_file, char *file_path,
	struct stat f)
{
	(*curr_file)->modes[0] = get_file_entry_type(f.st_mode);
	(*curr_file)->modes[1] = (f.st_mode & S_IRUSR) ? 'r' : '-';
	(*curr_file)->modes[2] = (f.st_mode & S_IWUSR) ? 'w' : '-';
	(*curr_file)->modes[3] = third_permission_mode_handler(f.st_mode, ISUSR);
	(*curr_file)->modes[4] = (f.st_mode & S_IRGRP) ? 'r' : '-';
	(*curr_file)->modes[5] = (f.st_mode & S_IWGRP) ? 'w' : '-';
	(*curr_file)->modes[6] = third_permission_mode_handler(f.st_mode, ISGRP);
	(*curr_file)->modes[7] = (f.st_mode & S_IROTH) ? 'r' : '-';
	(*curr_file)->modes[8] = (f.st_mode & S_IWOTH) ? 'w' : '-';
	(*curr_file)->modes[9] = third_permission_mode_handler(f.st_mode, ISOTH);
	if ((*curr_file)->modes[1] != '-')
		(*curr_file)->modes[10] = extended_attributes_handler(file_path);
	else
		(*curr_file)->modes[10] = ' ';
}
