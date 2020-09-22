/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:22:18 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/15 06:55:50 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void                print_operation(t_asm *bler, t_operation *opera)
{
	t_operation     *oper;
	int             i = 1;
	t_argument      *args;

	oper = opera;
	args = opera->args;
	ft_printf("\nString: %s\n\n", bler->line);
	ft_printf("Operation name: %s\n", opera->name);
	ft_printf("Operation size: %d byte.\n", opera->op_size);
	ft_printf("Code type size: %d byte.\n", opera->code_type_arg);
	ft_printf("OPCODE: %.2x.\n", opera->op_code);
	ft_printf("addr: %d\n", opera->addr);
	if (oper->lbl)
		ft_printf("Label name: %s\n", oper->lbl->str);
	else
		ft_printf("\n");
	while (args)
	{
		ft_printf("ARG #%d ", i);
		if (args->detector == NUM_VAL)
			ft_printf("Value: %lld\n", args->num_val);
		else if (args->detector == STRING_VAL)
			ft_printf("Value: %s\n", args->str_val);
		if (args->type == T_REG)
			ft_printf("                Type:%s", "T_REG");
		else if (args->type == T_DIR)
			ft_printf("                Type:%s", "T_DIR");
		else if (args->type == T_IND)
			ft_printf("                Type:%s", "T_IND");
		ft_printf("\nARG SIZE: %d byte\n", args->args_size);
		args = args->next;
		i++;
		ft_printf("\n");
	}
	ft_printf("\n--------------------------------------\n");

}

void		check_end_line(t_asm *bler)
{
	char	buff[bler->line_len + 1];
	int		i;

	i = 0;
	ft_bzero(buff, bler->line_len + 1);
	if ((lseek(bler->fd, -bler->line_len, SEEK_CUR)) <= 0)
		error_printf(bler, NULL, NULL);
	read(bler->fd, &buff, bler->line_len);
	while (buff[i] != '\0')
	{
		if (buff[i] == COMMENT_CHAR || buff[i] == ALT_COMMENT_CHAR)
			break;
		else if (buff[i] == ' ' || buff[i] == '\t')
			i++;
		else
		{
			if (buff[ft_strlen(buff) - 1] == '\n')
				break;
			else
				error_printf(bler, ERROR_END_LINE, NULL);
		}
	}
}

void            pass_voids(t_asm *bler)
{
	if (bler->line)
		while (bler->line[bler->sym] && (' ' == bler->line[bler->sym]
	                                     || bler->line[bler->sym] == '\t'))
			bler->sym++;
}