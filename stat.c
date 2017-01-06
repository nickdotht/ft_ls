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

void get_stat(char *file)
{
  char buff[200];

  struct stat fileStat;
  if(stat(file ,&fileStat) < 0)
      return ;

  printf("Information for %s\n",file);
  printf("---------------------------\n");
  printf("File Size: \t\t%ld bytes\n",fileStat.st_size);
  printf("Number of Links: \t%lu\n",fileStat.st_nlink);
  printf("File inode: \t\t%lu\n",fileStat.st_ino);

  printf("File Permissions: \t");
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
  printf("\n");

  printf("Owner: %s\n", getpwuid(fileStat.st_uid)->pw_name);
  printf("Owner group: %s\n", getgrgid(fileStat.st_gid)->gr_name);
  printf("Last modified: %s\n", formatdate(buff, fileStat.st_mtime));

  printf("The file %s a symbolic link\n\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
}
