/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:33:27 by jrameau           #+#    #+#             */
/*   Updated: 2017/03/07 23:38:25 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int main(int ac, char **av) {
  t_flags flags;
  int     i;
  t_dirs *head;
  t_dirs *dirs;

  flags = 0;
  i = flag_handler(av + 1, &flags);
  dirs = dir_handler(av + i, ac - i);
  display_handler(NULL, dirs, flags, IS_NONEXISTENT);
  display_handler(NULL, dirs, flags, IS_NOTDIR);
  head = dirs;
  while (dirs) {
    if (dirs->status == IS_DIR) {
      dirs->files = file_handler(dirs, flags);
      display_handler(head, dirs, flags, IS_DIR);
      dirs->next = subdir_handler(dirs->next, dirs->sub_dirs);
      if (!is_last_dir(dirs))
        printf("\n");
    }
    dirs = dirs->next;
  }
  memory_handler(&dirs, DIRS_MEM);
  exit(0);
}
