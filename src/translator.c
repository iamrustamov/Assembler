/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:22:15 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/15 06:45:00 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Главный переводчик в байт-код устроен таким образом:
** на вход получаем струткуру в которой все хранится,
** данные которые нужно переписать, и кол-во байтов
** которые требуется переписать. С помощью битовых операций
** мы проходимся по данным и с помощью маски 0xFF вытаскиваем
** два последних октета.
*/

void			bc_conver(t_rec *rec, int data, int size)
{
	int			i;

	i = 0;
	rec->cur += size;
	while (size > i)
	{
		rec->final_code[rec->cur - i - 1] = (char)((data >> (i * 8)) & 0xFF);
		i++;
	}
}

/*
** Бывают операции которые имеют код типов аргументов,
** этот код так же нужно генерировать.
** Мы просто проходимся по регистрам операции и выполняем
** битовые операции.
*/

char			code_type_arg(t_operation *oper)
{
	char		res;
	int			i;
	t_argument	*args;

	i = 0;
	res = 0;
	args = oper->args;
	while (i < 3 || args)
	{
		if (args)
		{
			if (args->type == T_REG)
				res |= 1;
			else if (args->type == T_DIR)
				res |= 2;
			else if (args->type == T_IND)
				res |= 3;
			args = args->next;
		}
		res = res << 2;
		i++;
	}
	return (res);
}

/*
** Как мы знаем T_DIR может хранить в себе либо число, либо метку.
** Данная функция помогат нам понять какое значение нам записать
** вместо метки, а записать нужно относительный адрес от операции до
** нужной метки. Если это просто число, то нужно просто его вписать.
*/

int				lbl_adr(t_argument *arg, t_asm *bler, t_operation *oper)
{
	t_operation	*new;

	new = bler->oper;
	while (new)
	{
		if (new->lbl && ft_strlen(arg->str_val) ==
				ft_strlen(new->lbl->str) &&
					!ft_strncmp(arg->str_val, new->lbl->str,
						ft_strlen(arg->str_val)))
			return (new->addr - oper->addr);
		new = new->next;
	}
	error_printf(bler, ERROR_LBLS_NOT, NULL);
	return (0);
}

/*
** В данной функции мы переводим транслируем
** операции(точнее их регистры) в байт-код.
*/

void			opcode_to_bytecode(t_asm *bler)
{
	t_operation	*oper;
	t_rec		*rec;
	t_argument	*args;

	rec = &bler->record;
	oper = bler->oper;
	while (oper)
	{
		args = oper->args;
		if (oper->name != NULL)
		{
			bc_conver(rec, oper->op_code, 1);
			if (oper->code_type_arg)
				bc_conver(rec, code_type_arg(oper), oper->code_type_arg);
			while (args)
			{
				if (args->detector == NUM_VAL)
					bc_conver(rec, (int)args->num_val, args->args_size);
				else
					bc_conver(rec, lbl_adr(args, bler, oper), args->args_size);
				args = args->next;
			}
		}
		oper = oper->next;
	}
}

/*
** В данной функции начинается весь процесс записи данных в .cor файл
** Для начала проходимся и подсчитываем размер исполняемго когда.
** Далее инициализируем переменные, чтоб их использовать в процессе записи.
** В первом вызове bytecode_conversion записываем Magic Header.
** Далее переписывем имя и сдвигаем курсор на нужное кол-во байтов.
** Вставляем размер файла, который мы вычисляли ранее.
** Переписываем комментарий и так же сдвигаем курсор.
** После, начинаем транслировать операции записывая их в структуру.
** И в последний момент вставляем содержимое структуры в файл.
*/

void			recorder(t_asm *bler)
{
	t_rec		*rec;

	get_exec_code_size(bler);
	rec_init(bler);
	rec = &bler->record;
	bc_conver(rec, COREWAR_EXEC_MAGIC, 4);
	ft_memcpy(&rec->final_code[rec->cur], bler->data->name,
		ft_strlen(bler->data->name));
	rec->cur += PROG_NAME_LENGTH + 4;
	bc_conver(rec, bler->exec_code_size, 4);
	ft_memcpy(&rec->final_code[rec->cur], bler->data->comment,
		ft_strlen(bler->data->comment));
	rec->cur += COMMENT_LENGTH + 4;
	opcode_to_bytecode(bler);
	write(bler->record.file_fd, rec->final_code, rec->file_size);
}
