/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	op_zjmp(t_vm *vm, t_carriage *cursor)
{
	int value;
	int addr;

	cursor->steps_next_oper += OP_CODE_SIZE;
	value = determine_value(cursor->op_args[0], vm, cursor);
	addr = ((value % IDX_MOD) + cursor->pos) % MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	if (cursor->carry)
	{
		cursor->pos = (addr);
		cursor->steps_next_oper = 0;
	}
	if (vm->logs)
		ft_printf("P %4d | zjmp %d %s\n",
			cursor->id,
			value,
			(cursor->carry) ? "OK" : "FAILED");
}
