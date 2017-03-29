#include "ft_ls.h"

void move_subdir(t_dirs **destRef, t_dirs **sourceRef)
{
  t_dirs *new;

  new = *sourceRef;
  *sourceRef = (*sourceRef)->next;
  new->next = *destRef;
  *destRef = new;
}

t_dirs *merge_splitted_subdirs(t_dirs *a, t_dirs *b)
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
    if (ft_strcmp(a->name, b->name) <= 0)
      move_subdir(tmp, &a);
    else
      move_subdir(tmp, &b);
    tmp = &((*tmp)->next);
  }
  return (res);
}

void split_subdir(t_dirs *sourceRef, t_dirs **frontRef, t_dirs **backRef)
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

void subdir_sort(t_dirs **sub_dirs)
{
  t_dirs *head;
  t_dirs *a;
  t_dirs *b;

  head = *sub_dirs;
  if (!head || !head->next)
    return ;
  split_subdir(head, &a, &b);
  subdir_sort(&a);
  subdir_sort(&b);
  *sub_dirs = merge_splitted_subdirs(a, b);
}

t_dirs *subdir_handler(t_dirs *next, t_dirs **sub_dirs)
{
  t_dirs *tmp;

  if (!*sub_dirs) {
    return next;
  }
  subdir_sort(sub_dirs);
  tmp = *sub_dirs;
  while (tmp->next) {
    tmp = tmp->next;
  }
  tmp->next = next;
  return (*sub_dirs);
}
