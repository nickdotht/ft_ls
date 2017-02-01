#include "ft_ls.h"

void    nonexistent_display(t_dirs *dirs)
{
    t_etarget   target;

    while (dirs)
    {
        if (dirs->status & IS_NONEXISTENT)
        {
            if (!(target.file = ft_strdup(dirs->name)))
                return ;
            error_handler(NONEXISTENT_ERR, target);
        }
        dirs = dirs->next;
    }
}

void    nondir_display(t_dirs *dirs, t_flags flags)
{
    if (flags & LONG_LISTING_FLAG)
        printf("LONG LISTING BELOW:\n");
    else
        printf("COLUMN VIEW BELOW:\n");
    while (dirs)
    {
        if (dirs->status & IS_NOTDIR)
            printf("file: %s\n", dirs->name);
        dirs = dirs->next;
    }
    printf("\n");
}

void    dir_display(t_dirs *dirs, t_flags flags)
{
    if (flags & LONG_LISTING_FLAG)
        printf("LONG LISTING BELOW:\n");
    else
        printf("COLUMN VIEW BELOW:\n");
    while (dirs)
    {
        if (dirs->status & IS_DIR)
        {
            printf("dir: %s\n", dirs->name);
            if (dirs->next)
                printf("\n");
        }
        dirs = dirs->next;
    }
}

void    display_handler(t_dirs *dirs, t_flags flags)
{
    nonexistent_display(dirs);
    nondir_display(dirs, flags);
    dir_display(dirs, flags);
}
