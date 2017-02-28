#include "ft_ls.h"

void        error_handler(t_errors err, t_etarget target)
{
    if (err & FLAG_ERR) {
        printf("ft_ls: illegal option -- %c\n", target.flag);
        printf("Try './ft_ls --help' for more information.\n");
        exit(1);
    }
    // else if (err & LONG_OPTION_ERR)
    //     printf("ft_ls: unrecognized option '--%s'\n", target.option);
    else if (err & FILE_ACCESS_ERR || err & NONEXISTENT_ERR)
        printf("ft_ls: %s: No such file or directory\n", target.file);
}
