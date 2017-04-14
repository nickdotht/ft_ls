#include "ft_ls.h"

void        error_handler(int err, t_etarget target)
{
    if (err == FLAG_ERR) {
        fprintf(stderr, "ls: illegal option -- %c\n", target.flag);
        fprintf(stderr, "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
        fprintf(stderr, "Try 'ls --help' for more information.\n");
        exit(1);
    }
    else if (err == FILE_ACCESS_ERR || err == NONEXISTENT_ERR)
        fprintf(stderr, "ls: %s: No such file or directory\n", target.file);
}
