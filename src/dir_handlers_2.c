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
  if (flags & NEWEST_FIRST_SORT_FLAG)
  {
    comparison = (*a)->date.tv_sec >= (*b)->date.tv_sec;
    if ((*a)->date.tv_sec == (*b)->date.tv_sec)
      comparison = (*a)->date.tv_nsec >= (*b)->date.tv_nsec;
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
