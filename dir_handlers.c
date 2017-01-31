#include "ft_ls.h"

t_dirs      *new_dir(char *name)
{
    t_dirs		*dir;

	if (!(dir = (t_dirs *)malloc(sizeof(*dir))))
		return (NULL);
	if (!name)
		dir->name = NULL;
	else
	{
		if (!(dir->name = ft_strnew(ft_strlen(name))))
			return (NULL);
		ft_strcpy(dir->name, name);
	}
	dir->next = NULL;
	return (dir);
}


void	    add_dir(t_dirs **alst, t_dirs *new)
{
    t_dirs  *tmp;
    t_dirs  *head;

    tmp = *alst;
    head = tmp;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
	*alst = head;
}

void	    dir_handler(char *arg, t_dirs **dirs)
{
	t_dirs *new;

	if (!(*dirs)->name)
	{
		*dirs = new_dir(arg);
		return ;
	}
	new =  new_dir(arg);
	add_dir(dirs, new);
}
