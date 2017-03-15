/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:09:38 by jrameau           #+#    #+#             */
/*   Updated: 2017/03/14 21:07:32 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int     ft_intlen(int num)
{
    if(num >= 100000) {
        if(num >= 10000000) {
            if(num >= 1000000000) return 10;
            if(num >= 100000000) return 9;
            return 8;
        }
        if(num >= 1000000) return 7;
        return 6;
    }
    else {
        if(num >= 1000) {
            if(num >= 10000) return 5;
            return 4;
        }
        else {
            if(num >= 100) return 3;
            if(num >= 10) return 2;
        }
        return 1;
    }
}
