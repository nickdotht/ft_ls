/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:33:27 by jrameau           #+#    #+#             */
/*   Updated: 2017/01/17 20:55:49 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int     get_longest_filesize(char *target_dir)
{
    struct dirent   *sd;
	DIR				*dir;
    int             longest;
    struct stat     fileStat;

    longest = 0;
	if (!(dir = opendir(target_dir)))
	{
		printf("ls: cannot access '%s': No such file or directory\n", target_dir);
		return (0);
	}
    while ((sd = readdir(dir)))
    {
        if (stat(ft_pathjoin(target_dir, sd->d_name), &fileStat) < 0)
            return (0);
        if (longest < ft_intlength(fileStat.st_size))
            longest = ft_intlength(fileStat.st_size);
    }
    closedir(dir);
    return (longest);
}

void ft_ls(char *target_dir) {
	DIR				*dir;
	struct dirent	*sd;
    int             longest_filesize;


    longest_filesize = get_longest_filesize(target_dir);
	if (!(dir = opendir(target_dir)))
	{
		printf("ls: cannot access '%s': No such file or directory\n", target_dir);
		return ;
	}
	while ((sd = readdir(dir)))
		get_stat(target_dir, sd->d_name, longest_filesize);

	closedir(dir);
}

int		main(int ac, char **av)
{
	char					*target;
	int						i;

	if (ac == 1)
	{
		target = ".";
		ft_ls(target);
	}
	else
	{
		i = 0;
		while (++i < ac)
		{
			target = av[i];
			ft_ls(target);
		}
	}
	return (0);
}
