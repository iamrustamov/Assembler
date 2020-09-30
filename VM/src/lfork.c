/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void		op_lfork(t_vm *vm, t_carriage *cursor)
{
	int value;

	cursor->steps_next_oper += OP_CODE_SIZE;
	value = determine_value(cursor->op_args[0], vm, cursor);
	add_to_start(&(vm->cursor), copy_cursor_lfork(value, cursor, vm));
	vm->cursor_num++;
	if (vm->logs)
		ft_printf("P %4d | lfork %d (%d)\n",
			cursor->id,
			value,
			cursor->pos + value);
}

t_carriage	*copy_cursor_lfork(int pos, t_carriage *cursor, t_vm *vm)
{
	t_carriage	*new;
	int			i;
	int			addr;

	i = 0;
	new = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	new->carry = cursor->carry;
	new->live_last_cycl = cursor->live_last_cycl;
	addr = ((cursor->pos + pos) % MEM_SIZE);
	if (addr < 0)
		addr += MEM_SIZE;
	new->pos = addr;
	while (i < REG_NUMBER)
	{
		new->reg[i] = cursor->reg[i];
		i++;
	}
	new->id = ++vm->cursor_id;
	return (new);
}
