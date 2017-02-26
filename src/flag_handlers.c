#include "ft_ls.h"

void long_option_flag(char *option, t_flags *flags) {
  t_etarget target;

  if (ft_strequ(option, "help"))
    help_handler();
  else if (ft_strequ(option, "recursive"))
    *flags |= RECURSIVE_FLAG;
  else if (ft_strequ(option, "all"))
    *flags |= ALL_FLAG;
  else if (ft_strequ(option, "reverse"))
    *flags |= REVERSE_FLAG;
  else {
    ft_strcpy(target.option, option);
    error_handler(LONG_OPTION_ERR, target);
  }
}

void set_flag(char *arg, t_flags *flags) {
  int i;
  t_etarget target;

  if (ft_strstartswith(arg, "--"))
    return long_option_flag(arg + 2, flags);
  i = 0;
  while (arg[++i]) {
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
    else {
      target.flag = arg[i];
      error_handler(FLAG_ERR, target);
    }
  }
}

void flag_handler(char **args, t_flags *flags) {
  int i;

  i = -1;
  while (args[++i]) {
    if (args[i][0] == '-') {
      set_flag(args[i], flags);
    }
  }
}
