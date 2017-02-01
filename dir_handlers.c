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

int         check_dir(char *name)
{
    struct stat s;
    int err;

    err = stat(name, &s);
    if(-1 == err)
    {
        if(ENOENT == errno)
            printf("ls: cannot access '%s': No such file or directory\n", name);
        return (0);
    }
    else
    {
        if(!S_ISDIR(s.st_mode))
        {
            printf("%s\n", name);
            return (0);
        }
    }
    return (1);
}

void	    dir_handler(char *arg, t_dirs **dirs)
{
	t_dirs *new;

    if (!check_dir(arg))
        return ;
	if (!(*dirs)->name)
	{
		*dirs = new_dir(arg);
		return ;
	}
	new =  new_dir(arg);
	add_dir(dirs, new);
}
