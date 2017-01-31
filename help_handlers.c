#include "ft_ls.h"

void		usage_help()
{
	printf("Usage: ./ft_ls [OPTION]... [FILE]...\n");
	printf("List information about the FILEs (the current directory by default).\n");
	printf("Sort entries alphabetically if -t is not specified.\n");
}

void		arguments_help()
{
	printf("Mandatory arguments to long options are mandatory for short options too.\n");
	printf("  -l\t\t\t\t\t\tuse a long listing format\n");
	printf("  -R, --recursive\tlist subdirectories recursively\n");
	printf("  -a, --all\t\t\t\tdo not ignore entries starting with .\n");
	printf("  -r, --reverse\t\treverse order while sorting\n");
	printf("  -t\t\t\t\t\t\tsort by modification time, newest first\n");
}

void		exits_help()
{
	printf("Exit status:\n");
 	printf(" 0  if OK,\n");
 	printf(" 1  if minor problems (e.g., cannot access subdirectory),\n");
 	printf(" 2  if serious trouble (e.g., cannot access command-line argument).\n");
}

void		help_handler(void)
{
	usage_help();
	printf("\n");
	arguments_help();
	printf("\n");
	exits_help();
 	exit(0);
}
