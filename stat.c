/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:09:38 by jrameau           #+#    #+#             */
/*   Updated: 2017/01/06 12:53:26 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char *formatdate(char *buff, time_t val)
{
  strftime(buff,200, "%b %d %H:%M", localtime(&val));
  return buff;
}

void get_stat(char *target_dir, char *file, t_format ll_format)
{
  char buff[200];
  struct stat fileStat;

  if(stat(ft_pathjoin(target_dir, file), &fileStat) < 0 || ft_strstartswith(file, "."))
      return ;

  /* printf("File inode: \t\t%lu\n",fileStat.st_ino); */

  printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
  printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
  printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
  printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");

  printf(" %*lu", ll_format.link, fileStat.st_nlink);
  printf(" %s", getpwuid(fileStat.st_uid)->pw_name);
  printf(" %s", getgrgid(fileStat.st_gid)->gr_name);
  printf(" %*ld", ll_format.fileSize, fileStat.st_size);
  printf(" %s", formatdate(buff, fileStat.st_mtime));
  printf(" %s\n",file);

  /* printf("The file %s a symbolic link\n\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not"); */
}
