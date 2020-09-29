/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	op_live(t_vm *vm, t_carriage *cursor)
{
	int id;

	vm->live_num_to_die++;
	cursor->live_last_cycl = vm->cycles;
	cursor->steps_next_oper += OP_CODE_SIZE;
	id = determine_value(cursor->op_args[0], vm, cursor);
	if (id <= -1 && id >= -((int)vm->player_num))
	{
		vm->champ_live = vm->champions[-id - 1];
		if (vm->live)
			ft_printf("A process shows that player %s is alive. Cycle - %d\n",
			vm->champions[-id - 1]->name, vm->cycles);
	}
	if (vm->logs)
		ft_printf("P %4d | live %d\n", cursor->id, id);
}
