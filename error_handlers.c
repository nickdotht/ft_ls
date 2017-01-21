#include "ft_ls.h"

void		option_error(char option)
{
	printf("ls: invalid option -- '%c'\n", option);
	printf("Try './ft_ls --help' for more information.\n");
	exit(2);
}

void		long_option_error(char *option)
{
	printf("ls: unrecognized option '--%s'\n", option);
	printf("Try './ft_ls --help' for more information.\n");
	exit(2);
}

void		access_error(char *target_dir)
{
	printf("ls: cannot access '%s': No such file or directory\n", target_dir);
}
