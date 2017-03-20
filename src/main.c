/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:33:27 by jrameau           #+#    #+#             */
/*   Updated: 2017/03/19 19:48:26 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void ft_display(t_dirs *dirs, t_dirs *head, t_flags flags)
{
  display_handler(NULL, dirs, flags, IS_NONEXISTENT);
  display_handler(NULL, dirs, flags, IS_NOTDIR);
  while (dirs && !dirs->is_last_dir)
  {
    if (dirs->status == IS_DIR)
    {
      dirs->files = file_handler(dirs, head, flags);
      while (dirs->files)
      {
        printf("%s\n", dirs->files->name);
        dirs->files = dirs->files->next;
      }
      exit(0);
      display_handler(head, dirs, flags, IS_DIR);
      dirs->next = subdir_handler(dirs->next, dirs->sub_dirs);
      if (!is_last_dir(dirs))
        printf("\n");
    }
    dirs = dirs->next;
  }
}

int main(int ac, char **av)
{
  t_flags flags;
  int     i;
  t_dirs *dirs;

  flags = 0;
  i = flag_handler(av + 1, &flags);
  dirs = dir_handler(av + i, ac - i, flags);
  ft_display(dirs, dirs, flags);
  memory_handler(&dirs, DIRS_MEM);
  exit(0);
}
