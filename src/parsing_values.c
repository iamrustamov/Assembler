#include <../includes/asm.h>

int check_comment(const char* str)
{
    int i;
    i = 0;

    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR || str[i] == '\0')
        return (0);
    return (1);
}

void error()
{
    printf("ERROR!");
    exit(1);
}

int write_name(char *str, char *name, short *ac, int c)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\"' && *ac == true) {
            *ac = false;
            i++;
            if (check_comment(&str[i]))
                error();
        }
        if (*ac == true) {
            name[c] = str[i];
            c++;
            if (c > PROG_NAME_LENGTH)
                error_print("ERROR");
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
    while (all->split_text[all->line])
    {
        len = write_name(all->split_text[all->line], all->name, &active, len);
        all->sym = 0;
        if (active == true)
            all->line++;
        else
            break;
    }
    all->name[len] = '\0';
    printf("%s", all->name);
    exit(23);
}

void                        record_name_comm(t_all *all, int flag)
{
    int     len;
    int     i;

    i = 0;
    if (flag)
        len = PROG_NAME_LENGTH;
    else
        len = COMMENT_LENGTH;
    while (all->split_text[len][i] && (all->split_text[len][i] == ' ' ||
                                       all->split_text[len][i] == '\t'))
        i++;
    if (all->split_text[len][i] && all->split_text[len][i] != '"')
    {
        error_print("ERROR: Wrong name\n");
        return ;
    }
    all->sym++;
//    while (i < len && all->split_text[len][i])
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

/*
 * Суть функции пропустить всё лишнее в виде комментариев и пустот.
 * Начинаем читать строки из сплита посимвольно.
 * Для этого открываем два цикла. Первый выдаёт одну линию текста
 * Второй цикл читает эту линию посимвольно.
 * Если это комментарий либо каретка со след. строкой, то выходит
 * из второго цикла и проходит сразу к следующей линии. Т.к. это нам
 * ни о чём не говорит. Парсить нечего.
 * А если встречает пустоты в виде пробелов и табуляций, то пропускает
 * их. А если уже находит что-то иное, а это может уже быть символ,
 * тогда выходит.
 * В all->pos сохраняются позиции, на которых они остановились, чтобы
 * в следующей функции мы знали от какой функции надо начинать парсить.
 */

int            miss_void(t_all *all)
{
    all->line= 0;
    all->sym = 0;

    while (all->split_text[all->line])
    {
        while (all->split_text[all->line][all->sym])
        {
            if (all->split_text[all->line][all->sym] == COMMENT_CHAR ||
                all->split_text[all->line][all->sym] ||
                all->split_text[all->line][all->sym] == '\n')
                break;
            if (all->split_text[all->line][all->sym] == ' ' ||
                all->split_text[all->line][all->sym] == '\t')
                all->sym++;
            else
                return (1);
        }
        all->line++;
        all->sym = 0;
    }
    all->line = 0;
    return (0);
}

/*
 * Все весь текст помещён в сплит,
 * теперь можно начинать парсинг и валидацию текста.
 * Создаётся массив f, под каждой ячейкой которого подразумеваются
 * флаги.
 * Для начала пропускаем все комментарии типа # и ;
 * и все лишние пробелы, табуляции и каретки перевода
 * в следующую строку. в функции miss_voids.
 * Если на этом файл закончился, значит это неполная карта и нужно
 * выводить ошибку.
 * Далее проверяем имя и комментарии.
 */

void            parsing_text(t_all *all)
{
    int         flag_name;
    int         flag_comm;
    int         runner;

    flag_comm = 0;
    flag_name = 0;
    while (!flag_name || !flag_comm)
    {
        miss_void(all);
        if (!all->split_text)
            error_print("ERROR: text is not valid\n");
        if (!ft_strncmp(all->split_text[0], NAME_CMD_STRING, 5))
        {
            flag_name = 1;
            record_name(all);
        }
        else if (ft_strncmp(all->split_text[0], COMMENT_CMD_STRING, 8))
        {
            flag_comm = 1;
        }
    }
}