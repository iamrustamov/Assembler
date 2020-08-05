#include <../includes/asm.h>

int                     write_name(char *str, char *name, short *ac, int c)
{
    int                 i;

    i = 0;

    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] != '\"')
        //TODO изменить здесь комментарий на адекватный
        error_print("Нет ковычек\n");
    while (str[i] != '\0')
    {
        if (str[i] == '\"' && *ac == true)
        {
            *ac = false;
            i++;
            if (check_comment(&str[i]))
                //TODO что за ошибка?
                error_print("ERROR.");
        }
        if (*ac == true)
        {
            name[c] = str[i];
            c++;
            if (c > PROG_NAME_LENGTH)
                error_print("ERROR NAME");
        }
        if (str[i] == '\"' && *ac == false && c == 0)
            *ac = true;
        i++;
    }
    return (c);
}

void                        record_name(t_all *all)
{
    short active;
    int len;

    len = 0;
    all->name = ft_memalloc(PROG_NAME_LENGTH);
    active = false;
    //TODO думаю этот способ не безопасен, т.к. при очистке может вызвать проблему очистки именно пропущенные ячейки от 0 до 4.
    all->split_text[all->line] = &all->split_text[all->line][5];
    while (all->split_text[all->line])
    {
        len = write_name(all->split_text[all->line], all->name, &active, len);
        if (active == true)
            all->line++;
        else
            break;
    }
    all->name[len] = '\0';
}