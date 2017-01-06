/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:33:27 by jrameau           #+#    #+#             */
/*   Updated: 2016/12/24 15:44:49 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		main(int ac, char **av)
{
	DIR *			dir;
	struct dirent	*sd;

	if (ac != 2)
		return (0);
		
	if (!(dir = opendir(av[1])))
	{
		printf("ls: %s: No such file or directory\n", av[1]);
		return (0);
	}

	while ((sd = readdir(dir)))
	{
		get_stat(sd->d_name);
	}

	closedir(dir);
	return (0);
}
