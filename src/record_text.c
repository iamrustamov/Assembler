#include <../includes/asm.h>

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

