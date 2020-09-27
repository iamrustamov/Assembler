/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		check_map(t_vm *vm)
{
	if (vm->cycles_to_die == vm->check_to_die || vm->cycles_to_die <= 0)
	{
		vm->checks++;
		delete_cursor(vm);
		if (vm->checks == MAX_CHECKS || vm->live_num_to_die >= NBR_LIVE)
		{
			vm->cycles_to_die -= CYCLE_DELTA;
			if (vm->logs)
				ft_printf("Cycle to die is now %zd\n", vm->cycles_to_die);
			vm->checks = 0;
		}
		vm->live_num_to_die = 0;
		vm->check_to_die = 0;
	}
}

void		delete_cursor(t_vm *vm)
{
	t_carriage	*cursor;

	vm->prev = NULL;
	cursor = vm->cursor;
	while (cursor)
	{
		if (vm->cycles_to_die <= 0 ||
		vm->cycles - cursor->live_last_cycl >= vm->cycles_to_die)
			cursor = remove_carriage(vm, cursor);
		else
		{
			vm->prev = cursor;
			cursor = cursor->next;
		}
	}
}

t_carriage	*remove_carriage(t_vm *vm, t_carriage *cursor)
{
	t_carriage	*tmp;

	vm->cursor_num--;
	tmp = cursor;
	cursor = cursor->next;
	if (vm->prev == NULL)
		vm->cursor = cursor;
	else
		vm->prev->next = cursor;
	if (vm->logs)
		ft_printf("Process %d hasn't lived for %zu cycles (CTD %zd)\n",
			tmp->id,
			vm->cycles - tmp->live_last_cycl,
			vm->cycles_to_die);
	free(tmp);
	return (cursor);
}
