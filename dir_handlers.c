#include "ft_ls.h"

t_dirs      *new_dir(char *name, t_status status)
{
    t_dirs		*dir;

	if (!(dir = (t_dirs *)malloc(sizeof(*dir))))
		return (NULL);
	if (!name)
		dir->name = NULL;
	else
	{
		if (!(dir->name = ft_strdup(name)))
            return (NULL);
        dir->status = status;
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

void         check_dir(char *name, t_status *status)
{
    struct stat s;

    *status = IS_DIR;
    if(stat(name, &s) == -1)
    {
        if(ENOENT == errno)
            *status = IS_NONEXISTENT;
    }
    else
    {
        if(!S_ISDIR(s.st_mode))
            *status = IS_NOTDIR;
    }
}

void	    dir_handler(char *arg, t_dirs **dirs)
{
	t_dirs      *new;
    t_status    status;

    status = 0;
    check_dir(arg, &status);
	if (!(*dirs)->name)
	{
		*dirs = new_dir(arg, status);
		return ;
	}
	new =  new_dir(arg, status);
	add_dir(dirs, new);
}
