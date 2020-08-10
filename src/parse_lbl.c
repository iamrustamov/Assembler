#include "../includes/asm.h"

int         check_line_of_label(t_all *all, int i)
{
    int     run;

    run = all->sym;
    /*
     * Если в строке двоеточие, то возвращаем единицу
     */
    if (i > 0 && all->split_text[all->line][i] == LABEL_CHAR)
        return (true);
    while (all->split_text[all->line][run])
    {
        if (all->split_text[all->line][run] == LABEL_CHAR)
            return (true);
        run++;
    }
    return (0);
}

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
    return (false);
}

int         check_lbls_char(t_all *all, int flag, int *lbl_flag, int i) //всё скопировано
{
    if (all->split_text[all->line][all->sym] == LABEL_CHAR)
        all->sym++;
    else if ((all->split_text[all->line][all->sym] == ' ' ||
            all->split_text[all->line][all->sym] == '\t' ||
            all->split_text[all->line][all->sym] == COMMENT_CHAR ||
            all->split_text[all->line][all->sym] == ALT_COMMENT_CHAR ||
            all->split_text[all->line][all->sym] == SEPARATOR_CHAR) && flag)
        return (true);
    /*
     *  Ищем второе двоеточие в линии с меткой. Если она есть, то выдаем ошибку.
     *  TODO а зачем в цикле дальше идём.
     */
    else if ((*lbl_flag = check_line_of_label(all, i)))
    {
        error_print("ERROR\nInvalid labels");
        while (all->split_text[all->line][all->sym] &&
                all->split_text[all->line][all->sym] != ',' &&
                all->split_text[all->line][all->sym] != ' ' &&
                all->split_text[all->line][all->sym] != '\t')
            all->sym++;
    }
    return (true);
}

/*
 * Т.к. мы не нашли операцию, здесь проверяем на наличие метки.
 * Сначала смотрим - на что идёт проверка?
 * Если на LABEL, тогда придаем f значение 0.
 */

void        check_lbl(int size, int *lbl_flag, t_types type ,t_all *all) //checkmet
{
        unsigned int    i;
        t_tokens        *token;
        int             flag;
        // эта функция вызывается несколько раз. В первый раз проверка делается на метку.
        if (type == LABEL)
            flag = 0;
        else
            flag = 1;
        i = all->sym;
        // Если там не стоит двоеточие, то выбрасывает ошибку.
        if (all->split_text[all->line][all->sym] != LABEL_CHAR && flag)
            error_print("ERROR\n");
        // Проверяем является ли это символом :. Если да, то пропускаем.
        // На всякий случай сохраняем эту позицию в переменной i.
        else if (all->split_text[all->line][all->sym] == LABEL_CHAR && flag)
        {
            //если это символ двоеточия, то тогда двигаем итератор символов
            all->sym++;
            // запоминаем где остановились.
            i = all->sym;
        }
        // FIXME Анализируем строку дальше после двоеточия, пока не наступила новая строка
        while (all->split_text[all->line][all->sym] &&
                all->split_text[all->line][all->sym] != '\n')
        {
            // в check_lbl_sym проверяем, что в метке допустимые символы из алфавита нижнего регистра и цифры
            // а в bad_lbl_char_manage проверяем, что кроме двоеточия
            if (!check_lbl_sym(all) && check_lbls_char(all, flag, lbl_flag, i))
                break ;
            all->sym++;
        }
        if (all->sym > 0) {
            if (!flag && all->split_text[all->line][all->sym - 1] == LABEL_CHAR)
                flag = all->sym - i - 1;
            else
                flag = all->sym - i;
        }
        token = create_token(all, type, -1, size);

}

/*
 * Проверяем метку
 */

int         parse_lbl(int *i, int *lbl_flag, t_oper *op, t_all *all)
{
    check_lbl(0, lbl_flag, LABEL, all);
    return (true);
}
