#include "../includes/asm.h"

void        keep_str(t_all *all)
{
    char    *buff;
    char    *name;
    int     byte;

    if (!(buff = ft_strnew(MEM_SIZE)))
        error_print();
    while ((byte = read(all->fd, buff, MEM_SIZE)) > 0)
    {
        buff[byte] = '\0';
        all->text = ft_move_text(all->text, buff);
    }
    printf("THIS IS ---------> %s", all->text);
}

void        ft_gen_parsing(char *file_name)
{
    t_all   *all;

    all = (t_all *)ft_memalloc(sizeof(t_all));
    all->fd = 0;
    all->fd = open(file_name, O_RDONLY);
    if (all->fd == -1)
        error_print();
    keep_str(t_all);
}

int         ft_validation_file(const char *str)
{
    if (ft_strcmp(&str[ft_strlen(str) - 2], ".s"))
        return (0);
    return (1);
}

int         main(int argc, char **argv)
{
    if (argc == 2)
    {
        ft_validation_file(argv[1]);
        ft_gen_parsing(argv[1]);
    }
    return (0);
}
