#include "../includes/asm.h"

t_oper  global_oper[17] =
        {
                {"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
                {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
                {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
                {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
                {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
                {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
                        "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
                {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
                        "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
                {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
                        "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
                {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
                {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
                        "load index", 1, 1},
                {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
                        "store index", 1, 1},
                {"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
                {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
                {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
                        "long load index", 1, 1},
                {"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
                {"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
                {{0}, 0, {0}, 0, 0, {0}, 0, 0}
        };

/*
 * Сначала проверяется нашлась ли операция.
 * Проверяется есть ли пробел или табуляция после имени операции?
 * Если нет, значит здесь ошибка. Очищаем операцию и ставим код -1 переменной i.
 */

void            check_oper_next_sym(int *i, t_oper *operation, t_all *all)
{
    if (operation->name[0])
    {
        if (all->split_text[all->line][all->sym + ft_strlen(operation->name)] != ' ' &&
            all->split_text[all->line][all->sym + ft_strlen(operation->name)] != '\t')
        {
            ft_bzero(operation, sizeof(t_oper));
            *i = -1;
        }
    }
}

t_oper          parse_operation(t_all *all, int *i)
{
    t_oper      oper;
    char        *oper_name;
    int         x;
    int         y;
    int         z;

    ft_bzero(&oper, sizeof(t_oper));
    x = all->sym;
    y = 0;
    while (16 >= y)
    {
        all->sym = x - 1;
        z = 0;
        oper_name = (char *)global_oper[y].name;
        // Сравниваем парсингуемое имя и имена операций.
        while (all->split_text[all->line][++all->sym] &&
               all->split_text[all->line][all->sym] == oper_name[z])
            z++;
        // Если перечисление операций не закончилось, а строка с совпадениями закончилась,
        // значит мы нашли операцию.
        if (16 > y && !oper_name[z])
        {
            oper = global_oper[y];
            *i = y;
        }
        y++;
    }
    check_oper_next_sym(i, &oper, all);
    return (oper);
}
