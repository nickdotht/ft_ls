/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 15:32:06 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/16 01:33:27 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H
#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/time.h>
#include <glob.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define MEMCHECK(x) if (!x) exit(2)

#define DIRS_MEM 1
#define ERROR_MEM 2

#define FLAG_ERR 1
#define FILE_ACCESS_ERR 2
#define NONEXISTENT_ERR 4

#define IS_NONEXISTENT 1
#define IS_NOTDIR 2
#define IS_DIR 4
#define IS_LINK 8
#define IS_UNREADABLE 16

#define ISUSR 1
#define ISGRP 2
#define ISOTH 4

#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_BOLD_GREEN "\x1b[32;1m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_BOLD_CYAN  "\x1b[96;1m"
#define ANSI_COLOR_RESET      "\x1b[0m"

#define IS_NONPRINTABLE(c) (c <= ' ' && c >= '~')

#define INIT_FORMAT 1
#define UPDATE_FORMAT 2
#define IDLE_FORMAT 4

typedef struct s_format {
  int link;
  int owner;
  int group;
  int fileSize;
  int date_month;
  int date_day;
  int date_hour;
  int date_minute;
  int date_year;
  int user_id;
  int group_id;
  int major;
  int minor;
} t_format;

typedef enum e_flags {
  LONG_LISTING_FLAG = 1, // -l
  RECURSIVE_FLAG = 2, // -R
  ALL_FLAG = 4, // -a
  REVERSE_FLAG = 8, // -r
  MODIFICATION_DATE_SORT = 16, // -t
  DISPLAY_UID_AND_GID = 32, // -n
  SUPRESS_OWNER = 64, // -g
  ONE_ENTRY_PER_LINE = 128, // -1
  COLUMN_DISPLAY = 256, // -C
  CREATION_DATE_SORT = 512, // -U
  LAST_ACCESS_DATE_SORT = 1024, // -a
  LAST_STATUS_CHANGE_SORT = 2048, // -c
  HIDE_CURR_AND_PREV_DIRS = 4096, // -A
  FILE_SIZE_SORT = 8192, // -S
  COLORED_OUTPUT = 16384 // -G
} t_flags;

typedef struct s_date {
  char *month;
  char *day;
  char *hour;
  char *minute;
  char *year;
  unsigned long long mtv_sec;
  unsigned long long mtv_nsec;
  unsigned long long atv_sec;
  unsigned long long atv_nsec;
  unsigned long long ctv_sec;
  unsigned long long ctv_nsec;
  unsigned long long birthtv_sec;
  unsigned long long birthtv_nsec;
} t_date;

typedef struct s_files {
  char *modes;
  long link;
  char *owner;
  unsigned int user_id;
  char *group;
  unsigned int group_id;
  long size;
  t_date date;
  char *name;
  int is_dir_info;
  long major;
  long minor;
  int is_chr_or_blk;
  int is_link;
  char *linked_to;
  int has_nonprintable_chars;
  char *display_name;
  int status;
  struct s_files *next;
  struct stat f; // Since I'm passing this I don't need to do stuffs like is_link or is_chr_or_blk
} t_files;

typedef struct s_dirs {
  char *name;
  int status;
  t_files *files;
  t_files *self;
  t_format format;
  int       is_default;
  int       is_unreadable;
  int       total_blocks;
  struct s_dirs *sub_dirs;
  struct s_dirs *next;
  int file_count;
  int max_file_len;
  t_date date;
  int is_subdir;
  char *display_name;
  int has_chr_or_blk;
  int has_valid_files;
} t_dirs;

typedef union u_etarget {
  char flag;
  char *file;
} t_etarget;


typedef union u_entries {
  t_files *files;
  char **file_names;
} t_entries;

void help_handler(void);
t_dirs *dir_handler(char **args, t_flags flags);
int flag_handler(char **args, t_flags *flags);
void error_handler(int err, t_etarget target);
void display_handler(t_dirs *head, t_dirs *dirs, t_flags flags, int target);
t_files *file_handler(t_dirs *dirs, t_flags flags);
void set_dir(char *path, t_dirs **dirs, char *subdir_name, t_flags flags);
void add_file(t_files **curr_file, t_dirs **dirs, t_flags flags, int format_option);
void add_dir(t_dirs **dirs, t_dirs *new);
void format_handler(t_format *format, t_files *file, int format_option);
int is_last_dir(t_dirs *dirs);
t_dirs *subdir_handler(t_dirs *next, t_dirs **sub_dirs, t_flags flags);
void memory_handler(void *mem_target, int target);
int is_last_nondir(t_dirs *dirs);
int is_only_dir(t_dirs *head);
void file_sort(t_files **files, t_flags flags);
int has_dirs(t_dirs *dirs);
void dir_sort(t_dirs **dirs, t_flags flags);
void reverse_files(t_files **files);
void reverse_dirs(t_dirs **dirs);
void ft_display(t_dirs *dirs, t_flags flags);
char get_file_entry_type(int mode);
char third_permission_mode_handler(int mode, int userType);
char **argument_handler(int ac, char **av);
t_format get_nondir_format(t_dirs **dirs, t_flags flags);
void print_handler(int fd, char *str, int format, char *target);
void lprint_handler(int fd, char *str, int format, char *target);
#endif
