/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:21:31 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/16 16:05:48 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void				clean_arguments(t_argument *args)
{
	t_argument		*tmp;

	tmp = args;
	while (tmp)
	{
		tmp->str_val ? free(tmp->str_val) : 0;
		tmp = tmp->next;
	}
}

void				clear_operations(t_operation *opers)
{
	t_operation		*tmp;

	tmp = opers;
	while (tmp)
	{
		tmp->name ? free(tmp->name) : 0;
		tmp->lbl && tmp->lbl->str ? free(tmp->lbl->str) : 0;
		tmp->lbl ? free(tmp->lbl) : 0;
		clean_arguments(tmp->args);
		tmp = tmp->next;
	}
}

void				clear_bler(t_asm *bler)
{
	if (bler->files_name != NULL)
		free(bler->files_name);
	clear_operations(bler->oper);
}

void				error_printf(t_asm *bler, char *text, char *line)
{
	char *buff;

	text ? ft_putstr_fd(text, 2) : 0;
	if (line)
	{
		buff = ft_strjoin("Pay attention to this line of file: ", line);
		ft_putstr_fd(buff, 2);
		ft_putchar_fd('\n', 2);
		free(buff);
	}
	if (bler)
		clear_bler(bler);
	exit(0);
}
