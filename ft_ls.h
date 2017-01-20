/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 15:32:06 by jrameau           #+#    #+#             */
/*   Updated: 2017/01/19 10:46:47 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
#include <dirent.h>
# include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "libft.h"

typedef struct		s_format
{
   int				link;
   int				owner;
   int				group;
   int				fileSize;
}					t_format;

#define				LONG_LISTING_FLAG 			1
#define				RECURSIVE_FLAG 				2
#define				ALL_FLAG 						4
#define				REVERSE_FLAG 					8
#define				NEWEST_FIRST_SORT_FLAG		16
int					g_flags = 0;
char				**g_target_dirs = NULL;

void				ft_ls(char *target_dir);
void				get_stat(char *target_dir, char *file, t_format ll_format);
t_format			format_handler(char *target_dir);
void				arguments_handler(char **av);

#endif
