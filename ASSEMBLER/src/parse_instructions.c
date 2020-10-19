/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:21:48 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/15 06:44:55 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** At first checking all symbols in string. If string have # or ;
** and it's not end of line - this is comment string.
*/

void			pass_comments(char *str)
{
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] &&
			(str[i] != ';' &&
				str[i] != '#'))
		i++;
	if (str[i] != '\0')
	{
		while (i < len)
		{
			str[i] = '\0';
			i++;
		}
	}
}

t_operation		*init_op_list(t_asm *bler)
{
	t_operation	*tmp;
	t_operation	*new_op;

	tmp = bler->oper;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!(new_op = (t_operation *)ft_memalloc(sizeof(t_operation))))
		error_printf(bler, "Error: Program did not allocate memory\n", NULL);
	if (!bler->oper)
		bler->oper = new_op;
	else
		tmp->next = new_op;
	return (new_op);
}

/*
** Сначала проверяем нашлись ли команда либо метка.
** Если да, то сначала создаём переменную для хранения операций.
** Далее добавляем метку. Если её нет, то ничего страшного, внутри проводится
** ещё одна проверка.
** Далее проверяем на операции.
** Если строка ещё есть, то пропускаем пробелы и табуляции.
** Если есть что-то ещё в строке, то вывод ошибки.
*/

void			parse_lbl_op(t_asm *bler)
{
	t_operation	*oper;
	char		*str;

	if (check_label(bler) ||
			check_op(bler))
	{
		oper = init_op_list(bler);
		add_lbls(bler, oper);
		add_op(bler, oper);
	}
	if (bler->line != NULL)
	{
		pass_voids(bler);
		str = bler->line + bler->sym;
		if (*str != '\0')
			error_printf(bler, ERROR_CONTANT, bler->line);
	}
}

void			parse_instructions(t_asm *bler)
{
	while (get_next_line(bler->fd, &bler->line) > FALSE)
	{
		bler->line_len = ft_strlen(bler->line);
		pass_comments(bler->line);
		parse_lbl_op(bler);
		bler->sym = 0;
		bler->line ? free(bler->line) : 0;
	}
	check_end_line(bler);
}
