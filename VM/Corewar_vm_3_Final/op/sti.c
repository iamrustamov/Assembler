/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_sti(t_vm *vm, t_carriage *cursor)
{
	int reg;
	int	value;
	int	addres1;
	int addres2;

	cursor->steps_next_oper += OP_ARGS_CODE_SIZE;
	reg = vm->arena[address(cursor)];
	value = cursor->reg[reg - 1];
	cursor->steps_next_oper += REG_S;
	addres1 = determine_value(cursor->op_args[1], vm, cursor);
	addres2 = determine_value(cursor->op_args[2], vm, cursor);
	write_bit(vm, cursor, value, (addres1 + addres2));
	if (vm->logs)
	{
		ft_printf("P %4d | sti r%d %d %d\n",
			cursor->id,
			reg,
			addres1,
			addres2);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			addres1,
			addres2,
			addres1 + addres2,
			cursor->pos + ((addres1 + addres2) % IDX_MOD));
	}
}
