/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_vm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			args_typ(t_vm *vm, t_carriage *cursor)
{
	unsigned char kod_arg;

	if (g_op_tab[cursor->op_cod - 1].cod_typ_args)
	{
		kod_arg = vm->arena[(cursor->pos + 1) % MEM_SIZE];
		cursor->op_args[0] = kod_args(kod_arg, 0);
		cursor->op_args[1] = kod_args(kod_arg, 1);
		cursor->op_args[2] = kod_args(kod_arg, 2);
	}
	else
		cursor->op_args[0] = DIR_CODE;
}

unsigned int	arg_size(unsigned char arg, t_carriage *cursor)
{
	if (arg == DIR_CODE)
		return (g_op_tab[cursor->op_cod - 1].dir_size);
	else if (arg == REG_CODE)
		return (REG_S);
	else if (arg == IND_CODE)
		return (IND_S);
	return (0);
}

unsigned int	step_by_step(t_carriage *cursor)
{
	int				i;
	unsigned int	step;

	i = 0;
	step = 0;
	step += OP_CODE_SIZE + g_op_tab[cursor->op_cod - 1].cod_typ_args;
	while (i < g_op_tab[cursor->op_cod - 1].arg)
	{
		step += arg_size(cursor->op_args[i], cursor);
		i++;
	}
	return (step);
}

int				valid_args(t_vm *vm, t_carriage *cursor)
{
	int				i;
	int				a;
	unsigned int	step;
	int				reg;

	a = 0;
	i = -1;
	step = (OP_CODE_SIZE + g_op_tab[cursor->op_cod - 1].cod_typ_args);
	while (++i < g_op_tab[cursor->op_cod - 1].arg)
	{
		while (g_op_tab[cursor->op_cod - 1].args[i][a])
		{
			if (cursor->op_args[i] == g_op_tab[cursor->op_cod - 1].args[i][a])
				break ;
			a++;
			if (g_op_tab[cursor->op_cod - 1].args[i][a] == 0 || a == 3)
				return (0);
		}
		reg = vm->arena[(cursor->pos + step) % MEM_SIZE];
		if ((cursor->op_args[i] == REG_CODE) && !(reg >= 1 && reg <= 16))
			return (0);
		step += arg_size(cursor->op_args[i], cursor);
		a = 0;
	}
	return (1);
}

void			move_cursor(t_carriage *cursor)
{
	cursor->pos += cursor->steps_next_oper;
	cursor->steps_next_oper = 0;
	ft_bzero(cursor->op_args, 3);
}
