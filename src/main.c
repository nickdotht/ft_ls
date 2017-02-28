/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:33:27 by jrameau           #+#    #+#             */
/*   Updated: 2017/02/28 05:43:35 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int main(int ac, char **av) {
  t_flags flags;
  int     i;

  flags = 0;
  if (ac) {
    i = flag_handler(av + 1, &flags);
    dir_handler(av + i, ac - i, flags);
  }
  exit(1);
}
