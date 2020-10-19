/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:21:55 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/29 12:49:14 by doberyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
** Проверка комментария после закрытия кавычек например .name "name"
** # Данный коммент проверяется на валидность
*/

int				check_comment(t_data *data, int pos)
{
	data->buff = &data->buff[pos];
	pass_delimetr(data);
	if (*data->buff == COMMENT_CHAR || *data->buff == ALT_COMMENT_CHAR
			|| *data->buff == '\0')
	{
		while (*data->buff != '\0')
			data->buff++;
		return (0);
	}
	else
		return (1);
}

/*
** Переписываем символ(с) в name или в comment в зависимости от
** переменной from. После записи сдвигаем позицию(pos) и проверяем длину
** записи на валидность.
*/

void			record(t_data *data, char c, t_asm *bler)
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
** Основная функция, где реализованна вся логика, проверки и обработка строки.
** В основном рычаги(write и item) отталкиваются от ковычек.
*/

void			write_name(t_data *data, t_asm *bler)
{
	int			i;

	i = 0;
	while (data->buff[i] != '\0')
	{
		if (data->write == TRUE)
		{
			if (data->buff[i] == '\"')
			{
				if (check_comment(data, i + 1))
					error_printf(bler, ERROR_GARBAGE, bler->line);
				data->write = FALSE;
				data->item++;
				break ;
			}
			else
				record(data, data->buff[i], bler);
		}
		else if (data->buff[i] == '\"' && data->pos == 0 &&
					data->write == FALSE)
			data->write = TRUE;
		else
			error_printf(bler, ERROR_COMM_LEN, NULL);
		i++;
	}
}

/*
** В данной функции мы определяем принадлежность строки
** к имени или комментарию. По итогу в переменной(char) from структуры data
** мы будем иметь букву 'n' или 'c'. В случае неудачи мы получаем ошибку.
*/

void			enrol_in(t_data *data, t_asm *bler)
{
	char		*str;

	str = data->buff;
	if (*str == '\0')
		return ;
	if (!ft_strncmp(NAME_CMD_STRING, str, 5) ||
			!ft_strncmp(COMMENT_CMD_STRING, str, 8))
	{
		data->from = str[1];
		if (data->from == 'n' && data->name == NULL)
		{
			data->buff = &str[5];
			bler->data->name = ft_strnew(PROG_NAME_LENGTH);
		}
		else if (data->from == 'c' && data->comment == NULL)
		{
			data->buff = &str[8];
			bler->data->comment = ft_strnew(COMMENT_LENGTH);
		}
		else
			error_printf(bler, ERROR_DOUBLE_NM_CMN, bler->line);
	}
	else if (check_comment(data, 0))
		error_printf(bler, ERROR_NM_CMN_N_EXIST, NULL);
}

void			parse_name_comm(t_asm *bler)
{
	t_data		*data;

	if (!(bler->data = (t_data *)ft_memalloc(sizeof(t_data))))
		error_printf(bler, ERROR_ALLOCATE, NULL);
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
