/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	op_ldi(t_vm *vm, t_carriage *cursor)
{
	int	value1;
	int	value2;
	int	reg;
	int addr;

	cursor->steps_next_oper += OP_ARGS_CODE_SIZE;
	value1 = determine_value(cursor->op_args[0], vm, cursor);
	value2 = determine_value(cursor->op_args[1], vm, cursor);
	reg = vm->arena[address(cursor)];
	addr = (cursor->pos + ((value1 + value2) % IDX_MOD)) % MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	cursor->reg[reg - 1] = bit_args(vm, addr, 4);
	cursor->steps_next_oper += REG_S;
	if (vm->logs)
	{
		ft_printf("P %4d | ldi %d %d r%d\n", cursor->id, value1, value2, reg);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			value1,
			value2,
			value1 + value2,
			cursor->pos + (value1 + value2) % IDX_MOD);
	}
}
