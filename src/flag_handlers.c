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
    target.flag = '-';
    error_handler(FLAG_ERR, target);
  }
}

void display_flag_handler(t_flags *flags, char f)
{
  if (f == '1')
  {
    if (*flags & COLUMN_DISPLAY)
      *flags &= ~COLUMN_DISPLAY;
    if (*flags & LONG_LISTING_FLAG)
      *flags &= ~LONG_LISTING_FLAG;
    *flags |= ONE_ENTRY_PER_LINE;
  }
  else if (f == 'l' || f == 'g')
  {
    if (f == 'g')
      *flags |= SUPRESS_OWNER;
    if (*flags & COLUMN_DISPLAY)
      *flags &= ~COLUMN_DISPLAY;
    if (*flags & ONE_ENTRY_PER_LINE)
      *flags &= ~ONE_ENTRY_PER_LINE;
    *flags |= LONG_LISTING_FLAG;
  }
  else
  {
    if (*flags & ONE_ENTRY_PER_LINE)
      *flags &= ~ONE_ENTRY_PER_LINE;
    if (*flags & LONG_LISTING_FLAG)
      *flags &= ~LONG_LISTING_FLAG;
    *flags |= COLUMN_DISPLAY;
  }
}

void sort_flag_handler(t_flags *flags, char f)
{
  if (f == 't' && !(*flags & FILE_SIZE_SORT))
    *flags |= MODIFICATION_DATE_SORT;
  else if (f == 'U')
  {
    if (*flags & LAST_ACCESS_DATE_SORT)
      *flags &= ~LAST_ACCESS_DATE_SORT;
    if (*flags & LAST_STATUS_CHANGE_SORT)
      *flags &= ~LAST_STATUS_CHANGE_SORT;
    *flags |= CREATION_DATE_SORT;
  }
  else if (f == 'u')
  {
    if (*flags & CREATION_DATE_SORT)
      *flags &= ~CREATION_DATE_SORT;
    if (*flags & LAST_STATUS_CHANGE_SORT)
      *flags &= ~LAST_STATUS_CHANGE_SORT;
    *flags |= LAST_ACCESS_DATE_SORT;
  }
  else if (f == 'c')
  {
    if (*flags & CREATION_DATE_SORT)
      *flags &= ~CREATION_DATE_SORT;
    if (*flags & LAST_ACCESS_DATE_SORT)
      *flags &= ~LAST_ACCESS_DATE_SORT;
    *flags |= LAST_STATUS_CHANGE_SORT;
  }
  else
  {
    if (*flags & MODIFICATION_DATE_SORT)
      *flags &= ~MODIFICATION_DATE_SORT;
    *flags |= FILE_SIZE_SORT;
  }
}

void set_flag(char *arg, t_flags *flags) {
  int i;
  t_etarget target;

  if (ft_strstartswith(arg, "--") && arg[2])
    return long_option_flag(arg + 2, flags);
  i = 0;
  while (arg[++i]) {
    if (arg[i] == 'R')
      *flags |= RECURSIVE_FLAG;
    else if (arg[i] == 'a')
      *flags |= ALL_FLAG;
    else if (arg[i] == 'r')
      *flags |= REVERSE_FLAG;
    else if (arg[i] == 'n')
      *flags |= DISPLAY_UID_AND_GID;
    else if (arg[i] == 'A')
      *flags |= HIDE_CURR_AND_PREV_DIRS;
    else if (arg[i] == 'G')
      *flags |= COLORED_OUTPUT;
    else if (arg[i] == 'U' || arg[i] == 't' || arg[i] == 'u' || arg[i] == 'c' || arg[i] == 'S')
      sort_flag_handler(flags, arg[i]);
    else if (arg[i] == '1' || arg[i] == 'l' || arg[i] == 'C' || arg[i] == 'g')
      display_flag_handler(flags, arg[i]);
    else {
      target.flag = arg[i];
      error_handler(FLAG_ERR, target);
    }
  }
}

int flag_handler(char **args, t_flags *flags) {
  int i;

  i = -1;
  *flags |= COLUMN_DISPLAY;  
  while (args[++i]) {
    if (args[i][0] != '-')
      break;
    if (ft_strequ(args[i], "--")) {
      i++;
      break;
    }
    if (args[i][0] == '-' && args[i][1])
      set_flag(args[i], flags);
    else
      break;
  }
  return (i > 0 ? i + 1 : 1);
}
