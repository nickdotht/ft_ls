/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 07:07:17 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 23:46:33 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_handler(int err, t_etarget target)
{
	if (err == FLAG_ERR)
	{
		print_handler(2, "ls: illegal option -- %s\n", 0, &target.flag);
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
