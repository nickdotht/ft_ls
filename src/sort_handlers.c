/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 02:37:27 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 20:55:58 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		modification_date_sort(char *n1, char *n2, t_date d1, t_date d2)
{
	int comparison;

	comparison = d1.mtv_sec > d2.mtv_sec;
	if (d1.mtv_sec == d2.mtv_sec)
	{
		comparison = d1.mtv_nsec > d2.mtv_nsec;
		if (d1.mtv_nsec == d2.mtv_nsec)
			comparison = ft_strcmp(n1, n2) < 0;
	}
	return (comparison);
}

int		creation_date_sort(char *n1, char *n2, t_date d1, t_date d2)
{
	int comparison;

	comparison = d1.birthtv_sec > d2.birthtv_sec;
	if (d1.birthtv_sec == d2.birthtv_sec)
	{
		comparison = d1.birthtv_nsec > d2.birthtv_nsec;
		if (d1.birthtv_nsec == d2.birthtv_nsec)
			comparison = ft_strcmp(n1, n2) < 0;
	}
	return (comparison);
}

int		last_access_date_sort(char *n1, char *n2, t_date d1, t_date d2)
{
	int comparison;

	comparison = d1.atv_sec > d2.atv_sec;
	if (d1.atv_sec == d2.atv_sec)
	{
		comparison = d1.atv_nsec > d2.atv_nsec;
		if (d1.atv_nsec == d2.atv_nsec)
			comparison = ft_strcmp(n1, n2) < 0;
	}
	return (comparison);
}

int		last_status_change_sort(char *n1, char *n2, t_date d1, t_date d2)
{
	int comparison;

	comparison = d1.ctv_sec > d2.ctv_sec;
	if (d1.ctv_sec == d2.ctv_sec)
	{
		comparison = d1.ctv_nsec > d2.ctv_nsec;
		if (d1.ctv_nsec == d2.ctv_nsec)
			comparison = ft_strcmp(n1, n2) < 0;
	}
	return (comparison);
}
