/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:22:03 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/15 06:44:59 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
 * Сравниваем метки всех операций.
 * Для этого берём метку одной операции, ищём совпадения. Если есть,
 * то выводим ошибку. Создается два цикла для поиска.
 * Один цикл для проверки, другой для прохода.
 */

int             check_lbl_dupl(t_asm *bler)
{
	t_operation *tmp_oper;
	t_operation *tmp2_oper;

	tmp_oper = bler->oper;
	while (tmp_oper)
	{
		tmp2_oper = tmp_oper->next;
		while (tmp2_oper)
		{
			if (tmp2_oper->lbl && tmp_oper->lbl)
				if (!ft_strcmp(tmp_oper->lbl->str, tmp2_oper->lbl->str))
					error_printf(bler, ERROR_DOUBLE_LBL, tmp2_oper->lbl->str);
			tmp2_oper = tmp2_oper->next;
		}
		tmp_oper = tmp_oper->next;
	}
	return (0);
}

void		parser_init(t_asm *bler)
{
	if (!(bler->data = (t_data *) ft_memalloc(sizeof(t_data))))
		error_printf(bler, "НЕ замалочилось", NULL); //FIXME АДЕКВАТНЫЙ КОМЕНТ НУЖЕН
	bler->data->name = ft_strnew(PROG_NAME_LENGTH);
	bler->data->comment = ft_strnew(COMMENT_LENGTH);
}

void        parser(t_asm *bler)
{
	parser_init(bler);
    parse_name_comm(bler);
	//ft_printf("NAME:    %s\n", bler->data->name);
	//ft_printf("COMMENT:    %s\n", bler->data->comment);
	parse_instructions(bler);
	check_lbl_dupl(bler);
	if (!bler->oper)
		error_printf(bler, ERROR_CONTANT, NULL);
}
