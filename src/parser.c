#include "../includes/asm.h"

/*
 * Читаем строку и проверяем - остались ли линии;
 * Проверка присутствия символов в строке;
 * Если это комментарии либо просто новые строки, то пропускаем эту строку;
 * Если же это просто пробел либо табуляция, то дальше идём по символам;
 * Когда доходим до символа, то возвращаемся, чтобы парсить.
 */

int            check_line(t_all *all)
{
    while (all->split_text[all->line])
    {
        while (all->split_text[all->line][all->sym])
        {
            if (all->split_text[all->line][all->sym] == COMMENT_CHAR ||
                all->split_text[all->line][all->sym] == ALT_COMMENT_CHAR ||
                all->split_text[all->line][all->sym] == '\n')
                break ;
            if (all->split_text[all->line][all->sym] == ' ' ||
                all->split_text[all->line][all->sym] == '\t')
                all->sym++;
            else
                return (true);
        }
        all->sym = 0;
        all->line++;
    }
    return (false);
}

/*
 * Сначала проверяем есть ли в настоящей строке операция.
 * Если её нет, то проаверяем на метку.
 */

void            parse_code(t_all *all)
{
    t_oper      oper;
    t_tokens    *token;
    int         i;
    int         size;
    int         lbl_flag; // incorrect_lbl

    i = -1;
    oper = parse_operation(all, &i);
    if (oper.name[0] == 0)
    {
        //size сохраняет позицию, чтобы в случае если там не метка, можно было парсить
        //заново на другие команды.
        size = all->sym;
        if (!parse_lbl(&i, &lbl_flag, &oper, all))
            return ;
    }
}

/*
 * Общий парсер кода
 */

void            parser(t_all *all)
{
    int         i;

    while (check_line(all))
    {
        if (all->split_text[all->line])
        {
            pass_void(all);
            parse_code(all);
        }
    }
}































///*
// * Пропускаем строки, если в них есть только пробелы и комментарии
// * Далее смотрим - остались ли ещё строки?
// * Если да, то пропускаем пробелы и табуляции.
// */
//void            pass_voids(t_all *all)
//{
//    while (all->split_text[all->line][all->sym] &&
//            all->split_text[all->line][all->sym] == ' ' &&
//            all->split_text[all->line][all->sym] == '\t')
//        all->sym++;
//}
//
//
//int              check_comment2(t_all *all)
//{
//    while (all->split_text[all->line])
//    {
//        all->sym = 0;
//        while (all->split_text[all->line][all->sym])
//        {
//            if (all->split_text[all->line][all->sym] == COMMENT_CHAR ||
//                    all->split_text[all->line][all->sym] == ALT_COMMENT_CHAR ||
//                    all->split_text[all->line][all->sym] == '\n')
//                break ;
//            if (all->split_text[all->line][all->sym] == ' ' || all->split_text[all->line][all->sym] == '\t')
//                all->sym++;
//            else
//                return (1);
//        }
//        all->line++;
//    }
//    return (0);
//}
//
//void            check_next_sym(t_all *all, t_oper *oper, int *i)
//{
//    if (oper->name[0]) //слишком похоже гарибшо
//    {
//        {
//            if (all->split_text[all->sym + ft_strlen(oper->name)] != '\t'
//                    && all->split_text[all->sym + ft_strlen(oper->name)] != ' ')
//            {
//                ft_bzero(oper, sizeof(t_oper));
//                i[0] = -1;
//            }
//        }
//    }
//}
///*
// * Здесь парсится имя операции;
// * varibales:
// * i - в виде числа указывает на какой строке операции, которую нашёл, остановился.
// * x - для поиска имени из глобальной переменной global_oper;
// * y - для чтение строки из глобальной переменной global_oper;
// * В цикле ставится 17, чтобы убедиться - пока все типы операций не исследованы;
// * Далее посимвольно в цикле сравниваются строки
// */
//
//t_oper                      parse_name(t_all *all, int *i, int x, int y) //operations
//{
//    t_oper      oper;
//    char        *str;
//    int         j;
//
//    j = all->sym;
//    ft_bzero(&oper, sizeof(oper));
//    while (x < 17)
//    {
//        all->sym = 0;
//        y = 0;
//        str = (char *)global_oper[x].name;
//        //TODO вот здесь заменить сравнение на ft_strcmp.
//        while (all->split_text[all->line][all->sym] &&
//                str[y] &&
//                all->split_text[all->line][all->sym++] == str[y])
//        {
//            all->sym++;
//            y++;
//        }
//        if (!str[y] && x < 17)
//        {
//            oper = global_oper[x];
//            (*i) = x;
//        }
//        x++;
//    }
//    check_next_sym(all, &oper, i);
//    return (oper);
//}
//
//void                        operations_find(t_oper *oper ,t_all *all, int *i, int *lbl_error)
//{
//
//}
//
//void                        parse_op(t_all *all, int i, int size, int lbl_error) //tokens
//{
//    t_oper       oper;
//    t_tokens     *token; // изменить имя.
//
//    oper = parse_name(all, &i, 0, 0);
//    if (!oper.name[0])
//    {
//        size = all->sym;
//        if (!operations_find(&oper ,all, &i, &lbl_error))
//            return ;
//    }
//}
//
//void            parsing(t_all *all) //parseng
//{
//    all->sym  = 0;
//    while (check_comment2(all))
//    {
//        if (all->split_text[all->line])
//        {
//            pass_voids(all);
//            parse_op(all, -1, 0, 0);
//        }
//    }
//}