/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:49:05 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/20 02:41:26 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_handler(int fd, char *str, int format, char *target)
{
	char	*new;
	char	*tmp;
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
			{
				tmp = new;
				new = ft_strjoinch(new, ' ');
				free(tmp);
			}
			tmp = new;
			MEMCHECK((new = ft_strjoin(new, target)));
			free(tmp);
			i += (str[i + 1] == 'd' || str[i + 1] == 's') ? 1 : 2;
		}
		else
		{
			tmp = new;
			MEMCHECK((new = ft_strjoinch(new, str[i])));
			free(tmp);
		}
	}
	ft_putstr_fd(new, fd);
	free(new);
}

void	lprint_handler(int fd, char *str, int format, char *target)
{
	char	*new;
	char	*tmp;
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
			tmp = new;
			MEMCHECK((new = ft_strjoin(new, target)));
			free(tmp);
			while (len++ < format)
			{
				tmp = new;
				new = ft_strjoinch(new, ' ');
				free(tmp);
			}
			i += (str[i + 1] == 'd' || str[i + 1] == 's') ? 1 : 2;
		}
		else
		{
			tmp = new;
			MEMCHECK((new = ft_strjoinch(new, str[i])));
			free(tmp);
		}
	}
	ft_putstr_fd(new, fd);
	free(new);
}
