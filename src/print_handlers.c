/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:49:05 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/20 20:45:48 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_handler(int fd, char *str, int format, char *target)
{
	char	*new;
	int		len;
	int		i;

	if (!format && !target)
		return (ft_putstr_fd(str, fd));
	MEMCHECK((new = ft_strnew(format + ft_strlen(str) +
		ft_strlen(target) - 2)));
	len = (int)ft_strlen(target);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '%')
		{
			while (len++ < format)
				new = ft_strjoinch(new, ' ');
			MEMCHECK((new = ft_strjoin(new, target)));
			i += (str[i + 1] == 'd' || str[i + 1] == 's') ? 1 : 2;
		}
		else
			new = ft_strjoinch(new, str[i]);
	}
	ft_putstr_fd(new, fd);
}

void	lprint_handler(int fd, char *str, int format, char *target)
{
	char	*new;
	int		len;
	int		i;

	if (!format && !target)
		return (ft_putstr_fd(str, fd));
	MEMCHECK((new = ft_strnew(format + ft_strlen(str) +
		ft_strlen(target) - 2)));
	len = (int)ft_strlen(target);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '%')
		{
			MEMCHECK((new = ft_strjoin(new, target)));
			while (len++ < format)
				new = ft_strjoinch(new, ' ');
			i += (str[i + 1] == 'd' || str[i + 1] == 's') ? 1 : 2;
		}
		else
			new = ft_strjoinch(new, str[i]);
	}
	ft_putstr_fd(new, fd);
	free(new);
}
