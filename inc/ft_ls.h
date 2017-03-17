/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 15:32:06 by jrameau           #+#    #+#             */
/*   Updated: 2017/03/16 23:00:41 by jrameau          ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define MEMCHECK(x) if (!x) exit(2)

#define DIRS_MEM 1
#define SUBDIRS_MEM 2
#define FILES_MEM 4

#define FLAG_ERR 1
#define FILE_ACCESS_ERR 2
#define NONEXISTENT_ERR 4

#define IS_NONEXISTENT 1
#define IS_NOTDIR 2
#define IS_DIR 4

typedef struct s_format {
  int link;
  int owner;
  int group;
  int fileSize;
  int date_month;
  int date_day;
  int date_hour;
  int date_minute;
} t_format;

typedef enum e_flags {
  LONG_LISTING_FLAG = 1,
  RECURSIVE_FLAG = 2,
  ALL_FLAG = 4,
  REVERSE_FLAG = 8,
  NEWEST_FIRST_SORT_FLAG = 16
} t_flags;

typedef struct s_date {
  char *month;
  char *day;
  char *hour;
  char *minute;
  unsigned long long unix;
} t_date;

typedef struct s_files {
  char *modes;
  long int link;
  char *owner;
  char *group;
  long int size;
  t_date date;
  char *name;
  struct s_files *next;
} t_files;

typedef struct s_dirs {
  char *name;
  int status;
  t_files *files;
  t_files *self;
  t_format format;
  int       is_default;
  int       is_unreadable;
  struct s_dirs *sub_dirs;
  struct s_dirs *next;
  t_date date;
} t_dirs;

typedef union u_etarget {
  char flag;
  char *file;
} t_etarget;


void ft_ls(char *target_dir);
void get_stat(char *target_dir, char *file, t_format ll_format);
void help_handler(void);
t_dirs *dir_handler(char **args, int num_args, t_flags flags);
int flag_handler(char **args, t_flags *flags);
void error_handler(int err, t_etarget target);
void display_handler(t_dirs *head, t_dirs *dirs, t_flags flags, int target);
t_files *file_handler(t_dirs *dirs, t_flags flags);
void set_dir(char *arg, t_dirs **dirs);
void add_file(t_files **curr_file, t_dirs **dirs, char *dir_name, char *file_name, t_flags flags);
void add_dir(t_dirs **dirs, t_dirs *new);
void format_handler(t_dirs **dirs, struct stat file_stat);
int is_last_dir(t_dirs *dirs);
t_dirs *subdir_handler(t_dirs *next, t_dirs *sub_dirs);
void memory_handler(void *mem_target, int target);
int is_last_nondir(t_dirs *dirs);
int is_only_dir(t_dirs *head);
void file_sort(t_files **files, t_flags flags);
int has_dirs(t_dirs *dirs);
void dir_sort(t_dirs **dirs);
unsigned long long get_dir_date(char *dir_name);
#endif
