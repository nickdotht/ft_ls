#include "ft_ls.h"

void        error_handler(t_errors err, t_etarget target)
{
    if (err & FLAG_ERR)
        printf("ls: invalid option -- '%c'\n", target.flag);
    else if (err & LONG_OPTION_ERR)
        printf("ls: unrecognized option '--%s'\n", target.option);
    else if (err & FILE_ACCESS_ERR)
        printf("ls: cannot access '%s': No such file or directory\n", target.file);
    if (err & LONG_OPTION_ERR || err & FLAG_ERR)
    {
        printf("Try './ft_ls --help' for more information.\n");
        exit(2);
    }
}
