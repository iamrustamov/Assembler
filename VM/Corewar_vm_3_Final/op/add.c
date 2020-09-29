/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_add(t_vm *vm, t_carriage *cursor)
{
	int reg1;
	int reg2;
	int reg3;
	int value;

	cursor->steps_next_oper += OP_ARGS_CODE_SIZE;
	reg1 = vm->arena[address(cursor)];
	cursor->steps_next_oper += REG_S;
	reg2 = vm->arena[address(cursor)];
	cursor->steps_next_oper += REG_S;
	value = cursor->reg[reg1 - 1] + cursor->reg[reg2 - 1];
	cursor->carry = (char)(!value);
	reg3 = vm->arena[address(cursor)];
	cursor->reg[reg3 - 1] = value;
	cursor->steps_next_oper += REG_S;
	if (vm->logs)
		ft_printf("P %4d | add r%d r%d r%d\n", cursor->id, reg1, reg2, reg3);
}
