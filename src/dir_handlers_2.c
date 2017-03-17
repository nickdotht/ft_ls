#include "ft_ls.h"

void move_dir(t_dirs **destRef, t_dirs **sourceRef)
{
  t_dirs *new;

  new = *sourceRef;
  *sourceRef = (*sourceRef)->next;
  new->next = *destRef;
  *destRef = new;
}

t_dirs *merge_splitted_dirs(t_dirs *a, t_dirs *b)
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
    move_dir(tmp, a->date.unix < b->date.unix ? &a : &b);
    tmp = &((*tmp)->next);
  }
  return (res);
}

void split_dir(t_dirs *sourceRef, t_dirs **frontRef, t_dirs **backRef)
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

int get_dir_date(char *dir_name)
{
  struct stat f;

  if (lstat(dir_name, &f) < 0)
    exit(2);
  return ft_atoi(ctime(f.st_mtime));
}

void dir_sort(t_dirs **dirs)
{
  t_dirs *head;
  t_dirs *a;
  t_dirs *b;

  head = *dirs;
  if (!head || !head->next)
    return ;
  split_dir(head, &a, &b);
  dir_sort(&a);
  dir_sort(&b);
  *dirs = merge_splitted_dirs(a, b);
}
