/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	op_xor(t_vm *vm, t_carriage *cursor)
{
	int	value1;
	int	value2;
	int	reg;

	cursor->steps_next_oper += OP_ARGS_CODE_SIZE;
	value1 = determine_value(cursor->op_args[0], vm, cursor);
	value2 = determine_value(cursor->op_args[1], vm, cursor);
	cursor->carry = (char)(!(value1 ^ value2));
	reg = vm->arena[address(cursor)];
	cursor->reg[reg - 1] = (value1 ^ value2);
	cursor->steps_next_oper += REG_S;
	if (vm->logs)
		ft_printf("P %4d | xor %d %d r%d\n", cursor->id, value1, value2, reg);
}
