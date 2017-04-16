#include "ft_ls.h"

void		usage_help()
{
	print_handler(1, "Usage: ./ft_ls [OPTION]... [FILE]...\n", 0, NULL);
	print_handler(1, "List information about the FILEs (the current directory by default).\n", 0, NULL);
	print_handler(1, "Sort entries alphabetically if -t is not specified.\n", 0, NULL);
}

void		arguments_help()
{
	print_handler(1, "Mandatory arguments to long options are mandatory for short options too.\n", 0, NULL);
	print_handler(1, "  -l\t\t\t\t\t\tuse a long listing format\n", 0, NULL);
	print_handler(1, "  -R, --recursive\tlist subdirectories recursively\n", 0, NULL);
	print_handler(1, "  -a, --all\t\t\t\tdo not ignore entries starting with .\n", 0, NULL);
	print_handler(1, "  -r, --reverse\t\treverse order while sorting\n", 0, NULL);
	print_handler(1, "  -t\t\t\t\t\t\tsort by modification time, newest first\n", 0, NULL);
}

void		exits_help()
{
	print_handler(1, "Exit status:\n", 0, NULL);
 	print_handler(1, " 0  if OK,\n", 0, NULL);
 	print_handler(1, " 1  if minor problems (e.g., cannot access subdirectory),\n", 0, NULL);
 	print_handler(1, " 2  if serious trouble (e.g., cannot access command-line argument).\n", 0, NULL);
}

void		help_handler(void)
{
	usage_help();
	print_handler(1, "\n", 0, NULL);
	arguments_help();
	print_handler(1, "\n", 0, NULL);
	exits_help();
 	exit(0);
}
