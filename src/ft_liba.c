#include "../includes/asm.h"

char        *ft_move_text(char *str1, char *str2)
{
    char    *res;
    int     len;

    if (!str1)
        return (ft_strdup(str2));
    else if (!str2)
        return (ft_strdup(str1));
    len = ft_strlen(str1) + ft_strlen(str2);
    if (!(res = (char *)ft_memalloc(len + 1)))
        return (NULL);
    res = ft_strcpy(res, str1);
    res = ft_strcat(res, str2);
    free(str1);
    return (res);
}

/*
 * Пропускаем все пробелы и табуляции;
 */

void            pass_void(t_all *all)
{
    while (all->split_text[all->line][all->sym]  &&
           (all->split_text[all->line][all->sym] == ' ' ||
            all->split_text[all->line][all->sym] == '\t'))
        all->sym++;
}