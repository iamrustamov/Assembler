#include "../includes/asm.h"

/*
 * Counting number of rows than to malloc memmory to split
 * and full every line to array.
 */

int        count_rows_num(char *str)
{
    int     i;
    int     count;

    count = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
            count++;
        i++;
    }
    if (str[i - 1] != '\n')
        count++;
    return (count);
}
// TODO в нашем split в конце строк ничего не стоит, а там он ставит коретку переноса строки

void        record_to_lines(char *text, t_all *all)
{
    int     row_count;

    row_count = count_rows_num(text);
    all->split_text = (char **)ft_memalloc(sizeof(char) * row_count);
    all->split_text = ft_strsplit(text, '\n');
    free(text);
    if (!all->split_text[0])
        error_print("ERROR: File is empty!");
}

char        *record_text(t_all *all)
{
    char    *buff;
    int     byte;
    char    *text;

    if (!(buff = ft_strnew(MEM_SIZE)))
        error_print("ERROR: memory not allocated.");
    while ((byte = read(all->fd, buff, MEM_SIZE)) > 0)
    {
        buff[byte] = '\0';
        text = ft_move_text(text, buff);
    }
    if (!text)
        error_print("ERROR: Not readable file.");
    return (text);
}

int            miss_comm_voids(t_all *all, int *runner)
{
    all->pos[0] = 0;
    all->pos[1] = 0;
    while (all->split_text[all->pos[0]])
    {
        if (all->split_text[all->pos[0]] == COMMENT_CHAR ||
                all->split_text[all->pos[0]] == ALT_COMMENT_CHAR ||
                all->split_text[all->pos[0]] == '\n')
            break;
        if (all->split_text[all->pos[0]] == ' ' ||
                all->split_text[all->pos[0]] == '\t')
                    all->split_text[all->pos[0]]++

    }
    return (runner);
}

void            parsing_text(t_all *all)
{
    char        f[2] = {0, 0};
    int         runner;

    runner = 0;
    while (!f[0] || !f[1])
    {
        miss_comm_voids(all, &runner);
    }
}

void        ft_gen_parsing(char *file_name)
{
    t_all   *all;

    all = (t_all *)ft_memalloc(sizeof(t_all));
    all->fd = 0;
    all->fd = open(file_name, O_RDONLY);
    if (all->fd == -1)
        error_print("ERROR: File did not open.");
    record_to_lines(record_text(all), all);
    close(all->fd);
    parsing_text(all);
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
