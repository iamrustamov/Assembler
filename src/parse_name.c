#include <fcntl.h>
#include "../includes/asm.h"

/*
 * Печатаем ошибку и выходим с exit
 */

void error(char *str)
{
    printf("%s", str);
    exit(1);
}

/*
 * Проверка комментария после закрытия кавычек например .name "name" # Данный коммент проверяется на валидность
 */

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

/*
 * Пропуск пробелов и табов
 */

int skip_void(char *str, int i)
{
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    return(i);
}

/*
 * Функция которая переписывает с line в name или comment
 */

void record(t_asm *bler, int code, int *c, int i)
{
	if (code < 2)
		bler->name[*c] = bler->line[i];
	else
		bler->comment[*c] = bler->line[i];
	*c = *c + 1;
	if (code < 2 && *c > PROG_NAME_LENGTH)
		error("Длина name больше!");
	else if (code > 1 && *c > COMMENT_LENGTH)
		error("Длина комментария больше!");
}

/*
 * Основная функция, где реализованна вся логика, проверки и обработка строки.
 */

int                     write_name(t_asm *bler, int *c ,int *code, int i)
{
    *code % 2 == 0 ? i = skip_void(bler->line, i) : i;
    if (bler->line[i] != '\"' && *code % 2 == 0)
		error("Нет ковычек\n");
    while (bler->line[i] != '\0' && *code < 4)
    {
        if (*code % 2 == 1)
        {
            if (bler->line[i] == '\"')
            {
            	i++;
                if (check_comment(&bler->line[i]))
                    error("После кавычек не комментария");
                *code = *code + 1;
            }
            else
				record(bler, *code, c, i);
        }
        if (bler->line[i] == '\"' && *code % 2 == 0 && *c == 0)
            *code = *code + 1;
        i++;
    }
    return (*c);
}

/*
 * Здесь начинается весь путь программы маллоки нужно куда нибудь засунуть.
 */

int			bytecode_conversion(char *src, int data, int size, int cur)
{
	int8_t		i;
	int			dup;

	i = 0;
	dup = size;
	while (dup > 0)
	{
		src[cur + dup - 1] = (char)((data >> i) & 0xFF);
		dup--;
		i += 8;
	}
	return (size);
}

void            parse_name_comm(t_asm *bler)
{
    int         flag;
    int         len;
    int			cur;
	int 		fd;

    cur = 0;
    bler->name = ft_strnew(PROG_NAME_LENGTH);
    bler->comment = ft_strnew(COMMENT_LENGTH);
    flag = 0;
    while(get_next_line(bler->fd, &bler->line) > 0 && flag < 4)
    {
    	if (flag == 0 || flag == 2)
    		len = 0;
        if (flag == 0 && !ft_strncmp(".name", bler->line, 5))
            len = write_name(bler , &len, &flag, 5);
        else if (flag == 2 && !ft_strncmp(".comment", bler->line, 8))
            len = write_name(bler , &len, &flag, 8);
        else
            len = write_name(bler , &len, &flag, 0);
    }
    if (flag != 4)
    	error("Файл не валиден");
	//bler->name = "ijokoiuytfghvbjnkmloiuytfghvbjnkmloiuygfhsedxfcgvhbjnkmol,p.,okijuhygtfrde4sdrftgyhujikolpokijuhygt6fr5d4es3we4drftgyhuijkolkiuh";
	//bler->comment = "COREWAR TEAM";
	fd = open("111111.cor", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	len = COMMENT_LENGTH + 16 + PROG_NAME_LENGTH;
    if (!(bler->write.final = ft_strnew(len)))
		error("Не выделилась память под строку!");
	cur += bytecode_conversion(bler->write.final, COREWAR_EXEC_MAGIC, 4, cur);
	ft_memcpy(&bler->write.final[cur], bler->name, ft_strlen(bler->name));
	cur += PROG_NAME_LENGTH + 4;
	bler->write.exec_size = 23;
	cur += bytecode_conversion(bler->write.final, bler->write.exec_size, 4, cur);
	ft_memcpy(&bler->write.final[cur], bler->comment, ft_strlen(bler->comment));
	cur += COMMENT_LENGTH + 4;
	write(fd, bler->write.final, len);
	printf("CUR: %d\n", cur);
    printf("name: %s\n", bler->name);
    printf("commment: %s\n", bler->comment);
    exit(12);
}