/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_st(t_vm *vm, t_carriage *cursor)
{
	int	value;
	int addres;
	int reg;

	cursor->steps_next_oper += OP_ARGS_CODE_SIZE;
	reg = vm->arena[address(cursor)];
	value = cursor->reg[reg - 1];
	cursor->steps_next_oper += REG_S;
	if (cursor->op_args[1] == REG_CODE)
	{
		addres = vm->arena[address(cursor)];
		cursor->reg[addres - 1] = value;
		cursor->steps_next_oper += REG_S;
	}
	else
	{
		addres = bit_args(vm, address(cursor), 2);
		write_bit(vm, cursor, value, (addres % IDX_MOD));
		cursor->steps_next_oper += IND_S;
	}
	if (vm->logs)
		ft_printf("P %4d | st r%d %d\n", cursor->id, reg, addres);
}
