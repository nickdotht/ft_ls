#include "ft_ls.h"

int     get_longest_filesize(char *target_dir)
{
	struct dirent   *sd;
	DIR				*dir;
	int             longest;
	struct stat     fileStat;

    longest = 0;
	if (!(dir = opendir(target_dir)))
	{
		printf("ls: cannot access '%s': No such file or directory\n", target_dir);
		return (0);
	}
    while ((sd = readdir(dir)))
    {
        if (stat(ft_pathjoin(target_dir, sd->d_name), &fileStat) < 0)
            return (0);
        if (longest < ft_intlength(fileStat.st_size))
            longest = ft_intlength(fileStat.st_size);
    }
    closedir(dir);
    return (longest);
}

int				get_longest_link(char *target_dir)
{
	struct dirent   *sd;
	DIR				*dir;
	int             longest;
	struct stat     fileStat;

    longest = 0;
	if (!(dir = opendir(target_dir)))
	{
		printf("ls: cannot access '%s': No such file or directory\n", target_dir);
		return (0);
	}
    while ((sd = readdir(dir)))
    {
        if (stat(ft_pathjoin(target_dir, sd->d_name), &fileStat) < 0)
            return (0);
        if (longest < ft_intlength(fileStat.st_nlink))
        {
            longest = ft_intlength(fileStat.st_nlink);
            printf("Longer file is %s\n", sd->d_name);
        }
    }
    closedir(dir);
    printf("OOOPPS: %d\n", longest);
    return (longest);
}

// TODO: CHeckout flags before doing this because the -a flag will be important to know if we should check dotfiles
t_format		format_handler(char *target_dir)
{
	t_format		tmp;

	tmp.fileSize = get_longest_filesize(target_dir);
	tmp.link = get_longest_link(target_dir);
	return (tmp);
}
