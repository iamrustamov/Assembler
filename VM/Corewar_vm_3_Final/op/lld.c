/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_lld(t_vm *vm, t_carriage *cursor)
{
	int value;
	int reg;

	cursor->steps_next_oper += OP_ARGS_CODE_SIZE;
	value = determine_value_lld(cursor->op_args[0], vm, cursor);
	cursor->carry = (char)(!value);
	reg = vm->arena[address(cursor)];
	cursor->reg[reg - 1] = value;
	cursor->steps_next_oper += REG_S;
	if (vm->logs)
		ft_printf("P %4d | lld %d r%d\n", cursor->id, value, reg);
}
