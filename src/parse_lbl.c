#include "../includes/asm.h"

/*
 *
 */

int         check_lbl_sym(t_all *all)
{
    int     i;

    i = 0;
    while (LABEL_CHARS[i])
    {
        if (LABEL_CHARS[i] != all->split_text[all->line][all->sym])
            i++;
        else
            return (true);
    }
    return (false)
}

/*
 * Сначала смотрим - на что идёт проверка?
 * Если на LABEL, тогда придаем f значение 0.
 */

void        check_lbl(int size, int *lbl_flag, t_types type ,t_all *all)
{
        unsigned int    i;
        t_tokens        *token;
        int             f;

        if (type == LABEL)
            f = 0;
        else
            f = 1;
        i = all->sym;
        if (all->split_text[all->line][all->sym] != LABEL_CHAR && f)
            error_print("ERROR\n");
        // Проверяем является ли это символом :. Если да, то пропускаем.
        // На всякий случай сохраняем эту позицию в переменной i.
        else if (all->split_text[all->line][all->sym] == LABEL_CHAR && f)
        {
            all->sym++;
            i = all->sym;
        }
        // FIXME Анализируем строку дальше после двоеточия, пока не наступила новая строка
        while (all->split_text[all->line][all->sym] &&
                all->split_text[all->line][all->sym] != '\n')
        {
            if (!check_lbl_sym(all) && ВОТ ЗДЕСЬ ПРОДОЛЖИТЬ.)
        }
}

/*
 * Проверяем метку
 */

int         parse_lbl(int *i, int *lbl_flag, t_oper *op, t_all *all)
{
    check_lbl(0, lbl_flag, LABEL, all);
    return (true);
}
