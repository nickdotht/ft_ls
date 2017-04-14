#include "ft_ls.h"

void move_dir(t_dirs **destRef, t_dirs **sourceRef)
{
  t_dirs *new;

  new = *sourceRef;
  *sourceRef = (*sourceRef)->next;
  new->next = *destRef;
  *destRef = new;
}

void handle_dir_merge_comparison(t_dirs **a, t_dirs **b, t_dirs **tmp, t_flags flags)
{
  int comparison;

  comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
  if (flags & MODIFICATION_DATE_SORT)
  {
    comparison = (*a)->date.mtv_sec >= (*b)->date.mtv_sec;
    if ((*a)->date.mtv_sec == (*b)->date.mtv_sec)
    {
      comparison = (*a)->date.mtv_nsec >= (*b)->date.mtv_nsec;
      if ((*a)->date.mtv_nsec == (*b)->date.mtv_nsec)
        comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
    }
    if (flags & CREATION_DATE_SORT)
    {
      comparison = (*a)->date.birthtv_sec >= (*b)->date.birthtv_sec;
      if ((*a)->date.birthtv_sec == (*b)->date.birthtv_sec)
      {
        comparison = (*a)->date.birthtv_nsec >= (*b)->date.birthtv_nsec;
        if ((*a)->date.birthtv_nsec == (*b)->date.birthtv_nsec)
          comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
      }
    }
    else if (flags & LAST_ACCESS_DATE_SORT)
    {
      comparison = (*a)->date.atv_sec >= (*b)->date.atv_sec;
      if ((*a)->date.atv_sec == (*b)->date.atv_sec)
      {
        comparison = (*a)->date.atv_nsec >= (*b)->date.atv_nsec;
        if ((*a)->date.atv_nsec == (*b)->date.atv_nsec)
          comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
      }
    }
    else if (flags & LAST_STATUS_CHANGE_SORT)
    {
      comparison = (*a)->date.ctv_sec >= (*b)->date.ctv_sec;
      if ((*a)->date.ctv_sec == (*b)->date.ctv_sec)
      {
        comparison = (*a)->date.ctv_nsec >= (*b)->date.ctv_nsec;
        if ((*a)->date.ctv_nsec == (*b)->date.ctv_nsec)
          comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
      }
    }
  }
  else if (flags & FILE_SIZE_SORT)
  {
    comparison = (*a)->self->size >= (*b)->self->size;
    if ((*a)->self->size == (*b)->self->size)
      comparison = ft_strcmp((*a)->name, (*b)->name) <= 0;
  }
  move_dir(tmp, comparison ? a : b);
}

t_dirs *merge_splitted_dirs(t_dirs *a, t_dirs *b, t_flags flags)
{
  t_dirs *res;
  t_dirs **tmp;

  res = NULL;
  tmp = &res;
  while (1)
  {
    if (!a)
    {
      *tmp = b;
      break;
    }
    else if (!b)
    {
      *tmp = a;
      break;
    }
    handle_dir_merge_comparison(&a, &b, tmp, flags); 
    tmp = &((*tmp)->next);
  }
  return (res);
}

void split_dirs(t_dirs *sourceRef, t_dirs **frontRef, t_dirs **backRef)
{
  t_dirs *slow;
  t_dirs *fast;

  slow = sourceRef;
  fast = sourceRef->next;
  while (fast)
  {
    fast = fast->next;
    if (fast)
    {
      slow = slow->next;
      fast = fast->next;
    }
  }
  *frontRef = sourceRef;
  *backRef = slow->next;
  slow->next = NULL;
}

void dir_sort(t_dirs **dirs, t_flags flags)
{
  t_dirs *head;
  t_dirs *a;
  t_dirs *b;

  head = *dirs;
  if (!head || !head->next)
    return ;
  split_dirs(head, &a, &b);
  dir_sort(&a, flags);
  dir_sort(&b, flags);
  *dirs = merge_splitted_dirs(a, b, flags);
}
