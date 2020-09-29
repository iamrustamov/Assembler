/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_arena.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		create_arena(t_vm *vm)
{
	int				id;
	unsigned int	pos;

	id = 0;
	pos = 0;
	while (id < (int)vm->player_num)
	{
		ft_memcpy(&(vm->arena[pos]), vm->champions[id]->exec_cod,
			(size_t)(vm->champions[id]->exec_cod_size));
		pos += MEM_SIZE / vm->player_num;
		id++;
	}
}

void		create_cursor(t_vm *vm)
{
	unsigned int	pos;
	int				id;

	pos = 0;
	id = 0;
	while (id < (int)vm->player_num)
	{
		add_to_start(&(vm->cursor), add_new_karet(vm, pos, id));
		pos += MEM_SIZE / vm->player_num;
		vm->cursor_num++;
		id++;
	}
}

void		add_to_start(t_carriage **list, t_carriage *new)
{
	if (new)
		new->next = *list;
	*list = new;
}

t_carriage	*add_new_karet(t_vm *vm, int pos, int id)
{
	t_carriage *cursor;

	cursor = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	cursor->id = ++vm->cursor_id;
	cursor->carry = false;
	cursor->pos = pos;
	cursor->reg[0] = -(vm->champions[id]->id);
	return (cursor);
}
