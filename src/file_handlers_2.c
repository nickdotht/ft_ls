#include "ft_ls.h"

void move_file(t_files **destRef, t_files **sourceRef)
{
  t_files *new;

  new = *sourceRef;
  *sourceRef = (*sourceRef)->next;
  new->next = *destRef;
  *destRef = new;
}

void handle_file_merge_comparison(t_files **a, t_files **b, t_files **tmp, t_flags flags)
{
  int comparison;

  // Try to do '<'' instead of '<=' to see if it would improve speed
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
    comparison = (*a)->size >= (*b)->size;
  move_file(tmp, comparison ? a : b);
}

t_files *merge_splitted_files(t_files *a, t_files *b, t_flags flags)
{
  t_files *res;
  t_files **tmp;

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
    handle_file_merge_comparison(&a, &b, tmp, flags);
    tmp = &((*tmp)->next);
  }
  return (res);
}

void split_file(t_files *sourceRef, t_files **frontRef, t_files **backRef)
{
  t_files *slow;
  t_files *fast;

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

void file_sort(t_files **files, t_flags flags)
{
  t_files *head;
  t_files *a;
  t_files *b;

  head = *files;
  if (!head || !head->next)
    return ;
  split_file(head, &a, &b);
  file_sort(&a, flags);
  file_sort(&b, flags);
  *files = merge_splitted_files(a, b, flags);
}
