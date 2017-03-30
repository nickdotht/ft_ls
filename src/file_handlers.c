/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:40:08 by jrameau           #+#    #+#             */
/*   Updated: 2017/03/30 01:30:24 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void file_modification_date_handler(t_date *date, struct stat f) {
  char buff[200];

  strftime(buff, 200, "%b", localtime(&(f.st_mtime)));
  MEMCHECK((date->month = ft_strdup(buff)));
  strftime(buff, 200, "%-d", localtime(&(f.st_mtime)));
  MEMCHECK((date->day = ft_strdup(buff)));
  strftime(buff, 200, "%H", localtime(&(f.st_mtime)));
  MEMCHECK((date->hour = ft_strdup(buff)));
  strftime(buff, 200, "%M", localtime(&(f.st_mtime)));
  MEMCHECK((date->minute = ft_strdup(buff)));
  strftime(buff, 200, "%Y", localtime(&(f.st_mtime)));
  MEMCHECK((date->year = ft_strdup(buff)));
  date->tv_sec = (unsigned long long)f.st_mtime;
  date->tv_nsec = (unsigned long long)f.st_mtimespec.tv_nsec;
}

char extended_attributes_handler(char *file_path)
{
  char res;
  acl_t acl;
  acl_entry_t entry;

  res = ' ';
  if (listxattr(file_path, NULL, 0, XATTR_NOFOLLOW) != 0 && opendir(file_path))
    return ('@');
  acl = acl_get_link_np(file_path, ACL_TYPE_EXTENDED);
  if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
  {
    acl_free(acl);
    acl = NULL;
  }
  if (acl)
    res = '+';
  return (res);
}

void get_file_info(t_files **curr_file, t_dirs **dirs, char *file_path, struct stat f)
{
  (*curr_file)->modes[0] = get_file_entry_type(f.st_mode);
  (*curr_file)->modes[1] = (f.st_mode & S_IRUSR) ? 'r' : '-';
  (*curr_file)->modes[2] = (f.st_mode & S_IWUSR) ? 'w' : '-';
  (*curr_file)->modes[3] = third_file_mode_handler(f.st_mode, ISUSR);
  (*curr_file)->modes[4] = (f.st_mode & S_IRGRP) ? 'r' : '-';
  (*curr_file)->modes[5] = (f.st_mode & S_IWGRP) ? 'w' : '-';
  (*curr_file)->modes[6] = third_file_mode_handler(f.st_mode, ISGRP);
  (*curr_file)->modes[7] = (f.st_mode & S_IROTH) ? 'r' : '-';
  (*curr_file)->modes[8] = (f.st_mode & S_IWOTH) ? 'w' : '-';
  (*curr_file)->modes[9] = third_file_mode_handler(f.st_mode, ISOTH);
  (*curr_file)->modes[10] = extended_attributes_handler(file_path);
  (*curr_file)->link = f.st_nlink;
  (*curr_file)->owner = getpwuid(f.st_uid) ? ft_strdup(getpwuid(f.st_uid)->pw_name) : NULL;
  (*curr_file)->group = getgrgid(f.st_gid) ? ft_strdup(getgrgid(f.st_gid)->gr_name) : NULL;
  (*curr_file)->user_id = (int)f.st_uid;
  (*curr_file)->group_id = (int)f.st_gid;
  (*curr_file)->size = f.st_size;
  file_modification_date_handler(&((*curr_file)->date), f);
  format_handler(dirs, *curr_file);
}

void add_file(t_files **curr_file, t_dirs **dirs, t_flags flags)
{
  struct stat f;
  char *dir_name;

  dir_name = (*dirs)->name;
  if (lstat(!dir_name ? (*curr_file)->name : ft_pathjoin(dir_name, (*curr_file)->name), &f) < 0 ||
  !((*curr_file)->modes = ft_strnew(11)))
    exit(2);
  get_file_info(curr_file, dirs, !dir_name ? (*curr_file)->name : ft_pathjoin(dir_name, (*curr_file)->name), f);
  (*dirs)->total_blocks += f.st_blocks;
  if (S_ISDIR(f.st_mode) && (flags & RECURSIVE_FLAG))
    set_dir(ft_pathjoin(dir_name, (*curr_file)->name), &((*dirs)->sub_dirs));
}

t_files *file_handler(t_dirs *dirs, t_flags flags) {
  DIR   *dir;
  struct dirent *sd;
  t_files *files;
  t_files **tmp;

  if (!(dir = opendir(dirs->name)))
  {
    dirs->is_unreadable = 1;
    return (NULL);
  }
  files = NULL;
  tmp = &files;
  dirs->total_blocks = 0;
  while ((sd = readdir(dir)))
  {
    if (!(flags & ALL_FLAG) && sd->d_name[0] == '.')
      continue ;
    MEMCHECK(((*tmp = (t_files *)ft_memalloc(sizeof(t_files)))));
    (*tmp)->name = ft_strdup(sd->d_name);
    add_file(tmp, &dirs, flags);
    tmp = &((*tmp)->next);
  }
  closedir(dir);
  file_sort(&files, flags);
  return (files);
}
