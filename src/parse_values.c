#include <../includes/asm.h>

int                         check_comment(const char* str)
{
    int i;
    i = 0;

    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR || str[i] == '\0')
        return (0);
    return (1);
}

/*
 * Флаг n указывает - было ли уже имя или нет.
 * Если имени не было, значит проверяем имя, присваив
 * строку имени.
 * Далее читаем строку и смотрим - если идут схожие символы,
 * то идём дальше по строке. Если нет - выходим, это точно
 * не строка имени.
 * Если ничего не остаётся в str, значит это имя.
 * Иначе возвращаем 0.
 */

int             valid_name_comm(t_all *all, int x, int y, int flag)
{
    char        *str;

    y = all->sym;

    if (!flag)
        str = NAME_CMD_STRING;
    else
        str = COMMENT_CMD_STRING;
    while (str[x])
    {
        if (all->split_text[all->sym])
        {
            x++;
            all->sym++;
        }
        else
            break ;
    }
    if (!str[x])
        return (1);
    all->sym = y;
    return (0);
}


//TODO разбить все функции на отдельные файлы.
//TODO Написать тесты для проверки функций записи name и comment
// TODO создать структуру если комента нет то выдаем ошибку
// TODO Предусмотреть отсутсвие ковычек

/*
 * flag_name and flag_comm are indicate that they are filled.
 * In cycle we are starting search of name and comment.
 * First condition - when text complete, but did not find name
 * and comment - printing error.
 *
 */
// TODO не парсит имя, в котором каждая буква слова на следующей строке
/*
 * Пример:
 * .name "t
 * e
 * s
 * t
 * "
 * Причина в том, что сталкивается с концом строки и на этом заканчивает.
 */

void            parsing_name_comm(t_all *all)
{
    int         flag_name;
    int         flag_comm;

    flag_comm = 0;
    flag_name = 0;

    while (flag_name + flag_comm != 2)
    {
        if (all->split_text[all->line] == NULL)
            error_print("ERROR: text have not valid name or comment.\n");
        if (!flag_name && !ft_strncmp(all->split_text[all->line], NAME_CMD_STRING, 5))
        {
            flag_name = 1;
            record_name(all);
        }
        else if (!flag_comm && !ft_strncmp(all->split_text[all->line], COMMENT_CMD_STRING, 8))
        {
            flag_comm = 1;
            record_comment(all);
        }
        all->line++;
    }
    printf("It's name    --->   %s\n", all->name);
    printf("It's comment --->   %s\n", all->comment);
}