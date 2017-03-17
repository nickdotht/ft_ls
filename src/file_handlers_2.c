#include "ft_ls.h"

void move_file(t_files **destRef, t_files **sourceRef)
{
  t_files *new;

  new = *sourceRef;
  *sourceRef = (*sourceRef)->next;
  new->next = *destRef;
  *destRef = new;
}

t_files *merge_splitted_files(t_files *a, t_files *b, t_flags flags)
{
  t_files *res;
  t_files **tmp;
  int condition;

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
    condition = (flags & NEWEST_FIRST_SORT_FLAG) ?
      a->date.unix >= b->date.unix :
      ft_strcmp(a->name, b->name) <= 0;
    move_file(tmp, condition ? &a : &b);
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
