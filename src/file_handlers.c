/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:40:08 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/12 12:38:33 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void file_date_handler(t_date *date, struct stat f, t_flags flags) {
  char buff[200];
  unsigned long long t;

  date->mtv_sec = (unsigned long long)f.st_mtime;
  date->mtv_nsec = (unsigned long long)f.st_mtimespec.tv_nsec;
  date->atv_sec = (unsigned long long)f.st_atime;
  date->atv_nsec = (unsigned long long)f.st_atimespec.tv_nsec;
  date->ctv_sec = (unsigned long long)f.st_ctime;
  date->ctv_nsec = (unsigned long long)f.st_ctimespec.tv_nsec;
  date->birthtv_sec = (unsigned long long)f.st_birthtime;
  date->birthtv_nsec = (unsigned long long)f.st_birthtimespec.tv_nsec;
  t = date->mtv_sec;
  if (flags & CREATION_DATE_SORT)
    t = date->birthtv_sec;
  if (flags & LAST_ACCESS_DATE_SORT)
    t = date->atv_sec;
  if (flags & LAST_STATUS_CHANGE_SORT)
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

char extended_attributes_handler(int has_unprintable_chars, char *file_path)
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
  if (has_unprintable_chars)
    res = '@';
  return (res);
}

char *serialize_file_name(char *name)
{
  char *new;
  int i;
  char c;

  MEMCHECK((new = ft_strnew(ft_strlen(name))));
  i = -1;
  while (name[++i]) {
    c = name[i];
    if (!IS_PRINTABLE(name[i]))
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

int has_unprintable_chars(char *s)
{
  int i;

  i = -1;
  while (s[++i])
    if (!IS_PRINTABLE(s[i]))
      return (1);
  return (0);
}

void file_permission_handler(t_files **curr_file, char *file_path, struct stat f)
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
  (*curr_file)->modes[10] = extended_attributes_handler((*curr_file)->has_unprintable_chars, file_path);
}

void get_file_info(t_files **curr_file, t_dirs **dirs, char *file_path, int format_option, t_flags flags)
{
  char buff[10000];
  struct stat f;

  f = (*curr_file)->f;
  file_permission_handler(curr_file, file_path, f);
  (*curr_file)->link = f.st_nlink;
  (*curr_file)->owner = getpwuid(f.st_uid) ? ft_strdup(getpwuid(f.st_uid)->pw_name) : NULL;
  (*curr_file)->group = getgrgid(f.st_gid) ? ft_strdup(getgrgid(f.st_gid)->gr_name) : NULL;
  (*curr_file)->user_id = (int)f.st_uid;
  (*curr_file)->group_id = (int)f.st_gid;
  (*curr_file)->size = f.st_size;
  if (S_ISCHR(f.st_mode) || S_ISBLK(f.st_mode))
  {
    (*curr_file)->major = (long)major(f.st_rdev);
    (*curr_file)->minor = (long)minor(f.st_rdev);
    (*curr_file)->is_chr_or_blk = 1;
    if (!(*dirs)->has_chr_or_blk)
      (*dirs)->has_chr_or_blk = 1;
  }
  if (S_ISLNK(f.st_mode))
  {
    (*curr_file)->is_link = 1;
    readlink(file_path, buff, 10000);
    if (has_unprintable_chars(buff)) {
      MEMCHECK(((*curr_file)->linked_to = serialize_file_name(buff)));      
    }
    else {
      MEMCHECK(((*curr_file)->linked_to = ft_strdup(buff)));
    }
  }
  file_date_handler(&((*curr_file)->date), f, flags);
  format_handler(&(*dirs)->format, *curr_file, format_option);
}

void add_file(t_files **curr_file, t_dirs **dirs, t_flags flags, int format_option)
{
  char *dir_name;
  char *file_path;
  int file_name_len;

  dir_name = (*dirs)->name;
  file_path = (*dirs)->status != IS_DIR ? (*curr_file)->name : ft_pathjoin(dir_name, (*curr_file)->name);
  if (lstat(file_path, &(*curr_file)->f) < 0 || !((*curr_file)->modes = ft_strnew(11)))
    exit(2);
  if (flags & LONG_LISTING_FLAG)
  {
    get_file_info(curr_file, dirs, file_path, format_option, flags);
    if ((*dirs)->status == IS_DIR)
      (*dirs)->total_blocks += (*curr_file)->f.st_blocks;
  }
  else
  {
    (*dirs)->file_count++;
    file_name_len = ft_strlen((*curr_file)->name);
    if (file_name_len > (*dirs)->max_file_len)
      (*dirs)->max_file_len = file_name_len;
  }
  if (S_ISDIR((*curr_file)->f.st_mode) && (flags & RECURSIVE_FLAG))
    set_dir(ft_pathjoin(dir_name, (*curr_file)->name), &((*dirs)->sub_dirs));
}

t_files *file_handler(t_dirs *dirs, t_flags flags) {
  DIR   *dir;
  struct dirent *sd;
  t_files *files;
  t_files **tmp;
  int format_option;
  char *file_name;

  if (!(dir = opendir(dirs->name)))
  {
    dirs->is_unreadable = 1;
    return (NULL);
  }
  files = NULL;
  tmp = &files;
  format_option = INIT_FORMAT;
  while ((sd = readdir(dir)))
  {
    if (!(flags & ALL_FLAG) && sd->d_name[0] == '.')
      continue ;
    MEMCHECK(((*tmp = (t_files *)ft_memalloc(sizeof(t_files)))));
    file_name = sd->d_name;
    if (has_unprintable_chars(sd->d_name)) {
      (*tmp)->display_name = serialize_file_name(sd->d_name);
      (*tmp)->has_unprintable_chars = 1;
    }
    (*tmp)->name = ft_strdup(sd->d_name);
    add_file(tmp, &dirs, flags, format_option);
    format_option = UPDATE_FORMAT;
    tmp = &((*tmp)->next);
  }
  closedir(dir);
  file_sort(&files, flags);
  return (files);
}
