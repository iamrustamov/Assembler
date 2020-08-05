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
 * Пропускаем строки, если в них есть только пробелы и комментарии
 * Далее смотрим - остались ли ещё строки?
 * Если да, то пропускаем пробелы и табуляции.
 */
void            pass_voids(t_all *all)
{
    while (all->split_text[all->line][all->sym] &&
            all->split_text[all->line][all->sym] == ' ' &&
            all->split_text[all->line][all->sym] == '\t')
        all->sym++;
}


void                        check_next_sym(t_oper *oper, t_all *all, int *i)
{

}

//

t_oper                      parse_name(t_all *all, int *i, int x, int y)
{
    t_oper      oper;
    char        *str;
    int         j;

    j = all->sym;
    ft_bzero(&oper, sizeof(oper));
    while (x < 17)
    {
        all->sym = j - 1;
        y = 0;
        str = (char *)global_oper[x].name;
        //TODO вот здесь заменить сравнение на ft_strcmp.
        while (all->split_text[all->line][all->sym] &&
                str[y] &&
                all->split_text[all->line][all->sym] == str[y])
        {
            all->sym++;
            y++;
        }
        if (!str[y] && x < 17)
        {
            oper = global_oper[x];
            (*i) = x;
        }
        x++;
    }
    check_next_sym(&oper, all, i);
    return (oper);
}

void                        parse_op(t_all *all, int run, int size, int lbl_error)
{
    t_oper       *oper;
    t_tokens     *token; // изменить имя.

    pass_voids(all);

    oper = parse_name(all, &run, 0, 0);
}

void            parsing_operations(t_all *all)
{
    t_oper      *oper;

    all->sym  = 0;
    while (check_comment(all->split_text[all->line]))
    {
        if (all->split_text[all->line])
        {
            pass_voids(all);
            parse_op(all, 0, 0, 0);
        }
    }
}