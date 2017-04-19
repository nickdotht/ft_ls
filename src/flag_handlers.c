#include "ft_ls.h"

void long_option_flag(char *option) {
  t_etarget target;

  if (ft_strequ(option, "help"))
    help_handler();
  else if (ft_strequ(option, "recursive"))
    g_flags |= RECURSIVE_FLAG;
  else if (ft_strequ(option, "all"))
    g_flags |= ALL_FLAG;
  else if (ft_strequ(option, "reverse"))
    g_flags |= REVERSE_FLAG;
  else {
    target.flag = '-';
    error_handler(FLAG_ERR, target);
  }
}

void display_flag_handler(char f)
{
  if (f == '1')
  {
    if (g_flags & COLUMN_DISPLAY)
      g_flags &= ~COLUMN_DISPLAY;
    if (g_flags & LONG_LISTING_FLAG)
      g_flags &= ~LONG_LISTING_FLAG;
    g_flags |= ONE_ENTRY_PER_LINE;
  }
  else if (f == 'l' || f == 'g')
  {
    if (f == 'g')
      g_flags |= SUPRESS_OWNER;
    if (g_flags & COLUMN_DISPLAY)
      g_flags &= ~COLUMN_DISPLAY;
    if (g_flags & ONE_ENTRY_PER_LINE)
      g_flags &= ~ONE_ENTRY_PER_LINE;
    g_flags |= LONG_LISTING_FLAG;
  }
  else
  {
    if (g_flags & ONE_ENTRY_PER_LINE)
      g_flags &= ~ONE_ENTRY_PER_LINE;
    if (g_flags & LONG_LISTING_FLAG)
      g_flags &= ~LONG_LISTING_FLAG;
    g_flags |= COLUMN_DISPLAY;
  }
}

void sort_flag_handler(char f)
{
  if (f == 't' && !(g_flags & FILE_SIZE_SORT))
    g_flags |= MODIFICATION_DATE_SORT;
  else if (f == 'U')
  {
    if (g_flags & LAST_ACCESS_DATE_SORT)
      g_flags &= ~LAST_ACCESS_DATE_SORT;
    if (g_flags & LAST_STATUS_CHANGE_SORT)
      g_flags &= ~LAST_STATUS_CHANGE_SORT;
    g_flags |= CREATION_DATE_SORT;
  }
  else if (f == 'u')
  {
    if (g_flags & CREATION_DATE_SORT)
      g_flags &= ~CREATION_DATE_SORT;
    if (g_flags & LAST_STATUS_CHANGE_SORT)
      g_flags &= ~LAST_STATUS_CHANGE_SORT;
    g_flags |= LAST_ACCESS_DATE_SORT;
  }
  else if (f == 'c')
  {
    if (g_flags & CREATION_DATE_SORT)
      g_flags &= ~CREATION_DATE_SORT;
    if (g_flags & LAST_ACCESS_DATE_SORT)
      g_flags &= ~LAST_ACCESS_DATE_SORT;
    g_flags |= LAST_STATUS_CHANGE_SORT;
  }
  else
  {
    if (g_flags & MODIFICATION_DATE_SORT)
      g_flags &= ~MODIFICATION_DATE_SORT;
    g_flags |= FILE_SIZE_SORT;
  }
}

void set_flag(char *arg) {
  int i;
  t_etarget target;

  if (ft_strstartswith(arg, "--") && arg[2])
    return long_option_flag(arg + 2);
  i = 0;
  while (arg[++i]) {
    if (arg[i] == 'R')
      g_flags |= RECURSIVE_FLAG;
    else if (arg[i] == 'a')
      g_flags |= ALL_FLAG;
    else if (arg[i] == 'r')
      g_flags |= REVERSE_FLAG;
    else if (arg[i] == 'n')
      g_flags |= DISPLAY_UID_AND_GID;
    else if (arg[i] == 'A')
      g_flags |= HIDE_CURR_AND_PREV_DIRS;
    else if (arg[i] == 'G')
      g_flags |= COLORED_OUTPUT;
    else if (arg[i] == 'U' || arg[i] == 't' || arg[i] == 'u' || arg[i] == 'c' || arg[i] == 'S')
      sort_flag_handler(arg[i]);
    else if (arg[i] == '1' || arg[i] == 'l' || arg[i] == 'C' || arg[i] == 'g')
      display_flag_handler(arg[i]);
    else {
      target.flag = arg[i];
      error_handler(FLAG_ERR, target);
    }
  }
}

int flag_handler(char **args) {
  int i;

  i = -1;
  g_flags |= COLUMN_DISPLAY;  
  while (args[++i]) {
    if (args[i][0] != '-')
      break;
    if (ft_strequ(args[i], "--")) {
      i++;
      break;
    }
    if (args[i][0] == '-' && args[i][1])
      set_flag(args[i]);
    else
      break;
  }
  return (i > 0 ? i + 1 : 1);
}
