#include "ft_ls.h"

void	long_option_handler(char *option, int *flags)
{
	if (ft_strequ(option, "help"))
		display_help();
	else if (ft_strequ(option, "recursive"))
		*flags |= RECURSIVE_FLAG;
	else if (ft_strequ(option, "all"))
		*flags |= ALL_FLAG;
	else if (ft_strequ(option, "reverse"))
		*flags |= REVERSE_FLAG;
	else
		long_option_error(option);
}

void	flag_handler(char *arg, int *flags)
{
	int		i;

	i = 0;
	if (ft_strstartswith(arg, "--"))
		return long_option_handler(arg + 2, flags);
	while (arg[++i])
	{
		if (arg[i] == 'l')
			*flags |= LONG_LISTING_FLAG;
		else if (arg[i] == 'R')
			*flags |= RECURSIVE_FLAG;
		else if (arg[i] == 'a')
			*flags |= ALL_FLAG;
		else if (arg[i] == 'r')
			*flags |= REVERSE_FLAG;
		else if (arg[i] == 't')
			*flags |= NEWEST_FIRST_SORT_FLAG;
		else
			option_error(arg[i]);
	}
}

void	argument_handler(char **args, int *flags)
{
	int		i;

	i = -1;
	while (args[++i])
	{
		if (ft_strstartswith(args[i], "-"))
			flag_handler(args[i], flags);
		// else
		// 	dirs_handler(args[i]);
	}
}
