#include "ft_ls.h"

void long_listing_display(t_dirs *dirs) {
  if (dirs->status & IS_DIR) {
    printf("Displaying files for %s\n", dirs->name);
    // if (dirs->files)
    //   printf("test link: %lu", dirs->files->link);
  } else
    printf("%s\n", dirs->name);
}

// void column_display(t_dirs *dirs, t_flags flags, t_status target) {
//   // Will work on this later.
// }

void nondir_display(t_dirs *dirs) {
  while (dirs) {
    if (dirs->status & IS_NOTDIR) {
      long_listing_display(dirs);
    }
    dirs = dirs->next;
  }
}

void dir_display(t_dirs *dirs) {
  printf("dir: %s\n", dirs->name);
  long_listing_display(dirs);
}

void display_handler(t_dirs *dirs, t_status target) {
  t_etarget etarget;

  if (target & IS_NONEXISTENT) {
    while (dirs) {
      if (dirs->status & IS_NONEXISTENT) {
        if (!(etarget.file = ft_strdup(dirs->name)))
          return;
        error_handler(NONEXISTENT_ERR, etarget);
      }
      dirs = dirs->next;
    }
  } else {
    // if (!(flags & LONG_LISTING_FLAG))
    //   return column_display(dirs, flags, target);
    if (target & IS_NOTDIR)
      nondir_display(dirs);
    else
      dir_display(dirs);
  }
}
