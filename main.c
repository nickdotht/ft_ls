/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:33:27 by jrameau           #+#    #+#             */
/*   Updated: 2017/01/23 20:05:01 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/* void    ft_ls(char *target_dir) { */
/* 	DIR				*dir; */
/* 	struct dirent	*sd; */
/*     t_etarget       target; */

/* 	if (!(dir = opendir(target_dir))) */
/*     { */
/*         ft_strcpy(target.file, target_dir); */
/* 		return error_handler(FILE_ACCESS_ERR, target); */
/*     } */
/* 	while ((sd = readdir(dir))) */
/* 		get_stat(target_dir, sd->d_name, ll_format); */
/* 	closedir(dir); */
/* } */

void	argument_handler(char **args, t_flags *flags, t_dirs **dirs)
{
	int		i;
    int     dirs_count;

	i = -1;
    dirs_count = 0;
	while (args[++i])
	{
		if (args[i][0] == '-')
			flag_handler(args[i], flags);
		else
        {
			dir_handler(args[i], dirs);
            dirs_count++;
        }
	}
    if (!dirs_count)
        dir_handler(".", dirs);
}

int		main(int ac, char **av)
{
	t_flags					flags;
	t_dirs  				*dirs;

	dirs = (t_dirs *)malloc(sizeof(*dirs));
    flags = 0;
    if (ac)
        argument_handler(av + 1, &flags, &dirs);
    /* print_dirs(dirs); */
    /* file_handler(flags, &dirs); */
    display_handler(dirs, flags);
	return (0);
}
