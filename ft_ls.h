/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 15:32:06 by jrameau           #+#    #+#             */
/*   Updated: 2017/02/04 09:50:58 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H
#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

typedef struct s_format {
  int link;
  int owner;
  int group;
  int fileSize;
} t_format;

typedef enum e_flags {
  LONG_LISTING_FLAG = 1,
  RECURSIVE_FLAG = 2,
  ALL_FLAG = 4,
  REVERSE_FLAG = 8,
  NEWEST_FIRST_SORT_FLAG = 16
} t_flags;

typedef enum e_errors {
  FLAG_ERR = 1,
  LONG_OPTION_ERR = 2,
  FILE_ACCESS_ERR = 4,
  NONEXISTENT_ERR = 8
} t_errors;

typedef struct s_files {
  char *modes;
  long int link;
  char *owner;
  char *group;
  long int size;
  char *date;
  char *name;
  struct s_files *next;
} t_files;

typedef enum e_status {
  IS_NONEXISTENT = 1,
  IS_NOTDIR = 2,
  IS_DIR = 4
} t_status;

typedef struct s_dirs {
  char *name;
  t_status status;
  t_files *files;
  t_format format;
  struct s_dirs *next;
} t_dirs;

typedef union u_etarget {
  char *option;
  char flag;
  char *file;
} t_etarget;

void ft_ls(char *target_dir);
void get_stat(char *target_dir, char *file, t_format ll_format);
void format_handler(t_format *format, t_dirs *dirs);
void help_handler(void);
void dir_handler(char **args, t_flags flags);
void flag_handler(char **args, t_flags *flags);
void error_handler(t_errors err, t_etarget target);
void display_handler(t_dirs *dirs, t_flags flags);
void get_dir_info(t_dirs **dirs, t_flags flags);
void file_handler(t_dirs **dirs, t_flags flags);
void set_dir(char *arg, t_dirs **dirs, t_flags flags);

#endif
