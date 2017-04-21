#include "libft.h"

char    *ft_pathjoin(char *p1, char *p2)
{
    if (!ft_strendswith(p1, "/"))
        return (ft_strjoin(ft_strjoinch(p1, '/'), p2));
    return (ft_strjoin(p1, p2));
}
