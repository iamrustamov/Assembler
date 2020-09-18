/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:21:55 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/15 06:44:56 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"


/*
 * Пропускаем все разделители(пробелы и табы)
 */

void	pass_delimetr(t_data *data)
{
	while ((*data->buff == ' ' || *data->buff == '\t') && *data->buff != '\0')
		data->buff++;
}

/*
 * Проверка комментария после закрытия кавычек например .name "name" # Данный коммент проверяется на валидность
 */

int         check_comment(t_data *data, int pos)
{
	data->buff = &data->buff[pos];
	pass_delimetr(data);
	if (*data->buff == COMMENT_CHAR || *data->buff == ALT_COMMENT_CHAR || *data->buff == '\0')
	{
		while (*data->buff != '\0')
			data->buff++;
		return (0);
	}
	else
		return (1);
}

/*
 * Переписываем символ(с) в name или в comment в зависимости от
 * переменной from. После записи сдвигаем позицию(pos) и проверяем длину
 * записи на валидность.
 */

void record(t_data *data, char c, t_asm *bler)
{
	if (data->from == 'n')
		data->name[data->pos] = c;
	else if (data->from == 'c')
		data->comment[data->pos] = c;
	data->pos++;
	if (data->from == 'n' && data->pos > PROG_NAME_LENGTH)
		error_printf(bler, ERROR_NAME_LEN, NULL);
	else if (data->from == 'c' && data->pos > COMMENT_LENGTH)
		error_printf(bler, ERROR_COMM_LEN, NULL);
}

/*
 * Основная функция, где реализованна вся логика, проверки и обработка строки.
 * В основном рычаги(write и item) отталкиваются от ковычек.
 */

void                     write_name(t_data *data, t_asm *bler)
{
	int i;

	i = 0;
	while (data->buff[i] != '\0')
	{
		if (data->write == TRUE)
		{
			if (data->buff[i] == '\"')
			{
				if (check_comment(data, i + 1))
					error_printf(bler, ERROR_WOKS_NM_CM, NULL);
				data->write = FALSE;
				data->item++;
				break;
			}
			else
				record(data, data->buff[i], bler);
		}
		else if  (data->buff[i] == '\"' && data->pos == 0 && data->write == FALSE)
			data->write = TRUE;
		else
			error_printf(bler, ERROR_COMM_LEN, NULL);
		i++;
	}
}

//FIXME Когда комментарий пустой, то выдает ошибку. Почему?
//FIXME Если комментарий перед именем и комментом, то выводится ошибка! Игрок Car из vm_champs/champs
//FIXME Когда нет коммента, то выводит, что длина слишком большая.
//FIXME неправильная реакция на файлы zother tests/unit_tests/error/

/*
 * В данной функции мы определяем принадлежность строки
 * к имени или комментарию. По итогу в переменной(char) from структуры data
 * мы будем иметь букву 'n' или 'c'. В случае неудачи мы получаем ошибку.
 */

void			enrol_in(t_data *data, t_asm *bler)
{
	char *str;

	str = data->buff;
	if (*str == '\0')
		return;
	if (!ft_strncmp(".name", str, 5) ||
			!ft_strncmp(".comment", str, 8))
	{
		data->from = str[1];
		if(data->from == 'n')
			data->buff = &str[5];
		else
			data->buff = &str[8];
	}
	else if (check_comment(data, 0))
			error_printf(bler, "Невалидная строка", NULL); // FIXME Нужен коммент нормальный
}

void            parse_name_comm(t_asm *bler)
{
	t_data *data;

	data = bler->data;
	while (data->item < 2 && get_next_line(bler->fd, &bler->line) > 0)
	{
		data->buff = bler->line;
		data->pos = (data->write == FALSE) ? 0 : data->pos;
		if (data->write == FALSE)
		{
			pass_delimetr(data);
			enrol_in(data, bler);
			pass_delimetr(data);
		}
		else if (data->write == TRUE)
			record(data, '\n', bler);
		write_name(data, bler);
		bler->line ? ft_strdel(&bler->line) : 0;
	}
	pass_voids(bler);
	if ((check_label(bler) == FALSE && check_op(bler) == FALSE) && bler->line)
		if (ft_isalnum(bler->line[bler->sym]))
			error_printf(bler, ERROR_UNKNOWN_TEXT, bler->line);
}