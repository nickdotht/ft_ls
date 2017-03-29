#include "ft_ls.h"

char get_correct_character(int mode, int isExec, int isSticky)
{
    if (mode & isExec)
    {
        if (mode & isSticky)
            return ('s');
        else
            return ('x');
    }
    else
    {
        if (mode & isSticky)
            return ('S');
        else
            return ('-');
    }
}

char third_file_mode_handler(int mode, int userType)
{
    if (userType == ISUSR)
        return get_correct_character(mode, S_IXUSR, S_ISUID);
    else if (userType == ISGRP)
        return get_correct_character(mode, S_IXGRP, S_ISGID);
    else
    {
        if (mode & S_IXOTH)
        {
            if (mode & S_ISTXT)
                return ('t');
            else
                return ('x');
        }
        else
        {
            if (mode & S_ISTXT)
                return ('T');
            else
                return ('-');
        }
    }
}