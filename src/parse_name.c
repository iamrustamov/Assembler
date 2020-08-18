#include "../includes/asm.h"

int check_comment(char *str)
{
    return (1);
}

int skip_void(char *str, int i)
{
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    return(0);
}

int                     write_name(t_asm *bler, int c ,int *code)
{
    int i;

    if (*code == 0)
        i = skip_void(bler->line, 5);
    else
        i = 0;
    if (bler->line[i] != '\"' && code == 0)
        //TODO изменить здесь комментарий на адекватный
        printf("Нет ковычек\n");
    while (bler->line[i] != '\0' && *code < 2)
    {
        if (*code == 1)
        {
            if (bler->line[i] == '\"') {
                i++;
                if (check_comment(&bler->line[i]))
                    //TODO что за ошибка?
                    printf("ERROR.");
                *code = *code + 1;
            }
            else
            {
                bler->name[c] = bler->line[i];
                c++;
                if (c > PROG_NAME_LENGTH)
                    printf("ERROR NAME");
            }
        }
        if (bler->line[i] == '\"' && *code == 0 && c == 0)
            *code = 1;
        i++;
    }
    return (c);
}

void            parse_name_comm(t_asm *bler)
{
    int         flag;
    int         len;

    bler->name = ft_memalloc(PROG_NAME_LENGTH);
    flag = 0;
    while(get_next_line(bler->fd, &bler->line) > 0 && flag < 3)
    {
        if (flag == 0 && !ft_strncmp(".name",bler->line,5))
            len = write_name(bler , 0, &flag);
        else if (flag == 1)
            len = write_name(bler , len, &flag);
        printf("%s\n", bler->line);
        printf("%s\n", bler->name);
    }
}