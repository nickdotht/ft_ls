/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 07:07:17 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 23:57:48 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	error_handler(int err, t_etarget target)
{
	char *tmp;
	char *flag;

	if (err == FLAG_ERR)
	{
		flag = ft_strnew(1);
		tmp = flag;
		flag = ft_strjoinch(flag, target.flag);
		free(tmp);
		print_handler(2, "ls: illegal option -- %s\n", 0, flag);
		free(flag);
		print_handler(2,
			"usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n",
			0, NULL);
		print_handler(2, "Try 'ls --help' for more information.\n", 0, NULL);
		exit(1);
	}
	else if (err == NONEXISTENT_ERR)
	{
		print_handler(2, "ls: %s: No such file or directory\n", 0,
			target.file);
	}
	else
		print_handler(2, "ls: %s: Permission denied\n", 0, target.file);
}
