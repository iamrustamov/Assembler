#include "asm.h"

t_op_list  op_tab[16] = {
        {"live", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 1, 0, 4},
        {"ld", 2, {{{0, 1, 1}}, {{1, 0, 0}}, {{0, 0, 0}}}, 2, 1, 4},
        {"st", 2, {{{1, 0, 0}}, {{1, 0, 1}}, {{0, 0, 0}}}, 3, 1, 4},
        {"add", 3, {{{1, 0, 0}}, {{1, 0, 0}}, {{1, 0, 0}}}, 4, 1, 4},
        {"sub", 3, {{{1, 0, 0}}, {{1, 0, 0}}, {{1, 0, 0}}}, 5, 1, 4},
        {"and", 3, {{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}}, 6, 1, 4},
        {"or", 3, {{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}}, 7, 1, 4},
        {"xor", 3, {{{1, 1, 1}}, {{1, 1, 1}}, {{1, 0, 0}}}, 8, 1, 4},
        {"zjmp", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 9, 0, 2},
        {"ldi", 3, {{{1, 1, 1}}, {{1, 1, 0}}, {{1, 0, 0}}}, 10, 1, 2},
        {"sti", 3, {{{1, 0, 0}}, {{1, 1, 1}}, {{1, 1, 0}}}, 11, 1, 2},
        {"fork", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 12, 0, 2},
        {"lld", 2, {{{0, 1, 1}}, {{1, 0, 0}}, {{0, 0, 0}}}, 13, 1, 4},
        {"lldi", 3, {{{1, 1, 1}}, {{1, 1, 0}}, {{1, 0, 0}}}, 14, 1, 2},
        {"lfork", 1, {{{0, 1, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 15, 1, 2},
        {"aff", 1, {{{1, 0, 0}}, {{0, 0, 0}}, {{0, 0, 0}}}, 16, 1, 4}
};

/*
 * Здесь ищется операция по названию из глобальной переменной выше.
 */

int             find_oper(char *str, int len)
{
    int         i;

    i = 0;
    while (i < 16)
    {
        if (ft_strnequ(op_tab[i].name, str, len))
            return (i);
        i++;
    }
    return (-1);
}

void            pass_voids(const char *str)
{
    int         i;

    i = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
}

int             check_label(char *str)
{
    int         i;

    i = 0;
    pass_voids(str);
    while (str[i] && str[i] != ':')
    {
        if (!ft_strchr(LABEL_CHARS, str[i]))
            return (0);
        i++;
    }
    if (i > 0 && str[i] == ':')
        return (1);
    else
        return (0);
}

int             check_op(char *str)
{
    int         i;

    i = 0;
    pass_voids(str);
    if (check_label(str))
        str = ft_strchr(str, ':') + 1;
    while (str[i] && ft_isalpha(str[i]))
        i++;
    if (i > 0 && find_oper(str, i) != -1) //TODO не находит в функции find_oper операцию.
        return (1);
    else
        return (0);
}



void            parse_lbl_op(t_asm *bler) // TODO get_lca
{
    t_operation *oper;
    int         i;

    i = 0;
    if (check_label(bler->line) || check_op(bler->line))
    {

    }
}

/*
 * Проверяем строку на наличие символов комментария
 * Если ещё не достигнуто конца строки, то обнуляем эту строку.
 */
void            pass_comments(t_asm *bler)
{
    int         i;

    i = 0;
    while (bler->line[i] &&
        bler->line[i] != ';' &&
        bler->line[i] != '#')
        i++;
    if (bler->line[i] != '\0')
        ft_bzero(bler->line, ft_strlen(bler->line));
}

void            parse_commands(t_asm *bler)
{
    while (get_next_line(bler->fd, &bler->line) > 0)
    {
        bler->line_len = ft_strlen(bler->line);
        pass_comments(bler);
        parse_lbl_op(bler);
    }
}
