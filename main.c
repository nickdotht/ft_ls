/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:33:27 by jrameau           #+#    #+#             */
/*   Updated: 2017/01/21 16:38:14 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void ft_ls(char *target_dir) {
	DIR				*dir;
	struct dirent	*sd;
	t_format		ll_format;

    	ll_format = format_handler(target_dir);
	if (!(dir = opendir(target_dir)))
		return access_error(target_dir);
	while ((sd = readdir(dir)))
		get_stat(target_dir, sd->d_name, ll_format);
	closedir(dir);
}

int		main(int ac, char **av)
{
	char					*target;
	int						i;
	int						flags;

	flags = 0;
	argument_handler(av, &flags);
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
