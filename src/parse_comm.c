#include <../includes/asm.h>

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

//TODO слишком длиннно


int                     write_comment(char *str, char *comment, short *ac, int c)
{
    int i;
    i = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] != '\"')
        error_print("Нет ковычек\n");
    while (str[i] != '\0')
    {
        if (str[i] == '\"' && *ac == true) {
            *ac = false;
            i++;
            if (check_comment(&str[i]))
                //TODO что за ошибка?
                error_print("ERROR\n");
        }
        if (*ac == true) {
            comment[c] = str[i];
            c++;
            if (c > COMMENT_LENGTH)
                error_print("ERROR COMMENT");
        }
        if (str[i] == '\"' && *ac == false && c == 0)
            *ac = true;
        i++;
    }
    return (c);
}

void                        record_comment(t_all *all)
{
    short active;
    int len;

    len = 0;
    all->comment = ft_memalloc(COMMENT_LENGTH);
    active = false;
    all->split_text[all->line] = &all->split_text[all->line][8];
    while (all->split_text[all->line])
    {
        len = write_comment(all->split_text[all->line], all->comment, &active, len);
        if (active == true)
            all->line++;
        else
            break;
    }
    all->comment[len] = '\0';
}
