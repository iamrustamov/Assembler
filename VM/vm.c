/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cod_oper(t_vm *vm, t_carriage *cursor)
{
	if (cursor->cycles_to_cod == 0)
	{
		cursor->op_cod = vm->arena[cursor->pos];
		if (vm->arena[cursor->pos] >= 0x01 && vm->arena[cursor->pos] <= 0x10)
			cursor->cycles_to_cod = g_op[cursor->op_cod - 1].cycles_exec;
	}
	if (cursor->cycles_to_cod > 0)
		cursor->cycles_to_cod--;
}

void	start_oper(t_vm *vm, t_carriage *cursor)
{
	unsigned i;

	if (cursor->op_cod >= 0x01 && cursor->op_cod <= 0x10)
	{
		args_typ(vm, cursor);
		if (valid_args(vm, cursor))
			g_op[cursor->op_cod - 1].func(vm, cursor);
		else
			cursor->steps_next_oper += step_by_step(cursor);
		if (cursor->steps_next_oper && vm->logs)
		{
			ft_printf("ADV %d (%0.4p -> %0.4p) ", cursor->steps_next_oper,
			cursor->pos, cursor->pos + cursor->steps_next_oper);
			i = 0;
			while (i < cursor->steps_next_oper)
			{
				ft_printf("%02x ", vm->arena[(cursor->pos + i)]);
				i++;
			}
			ft_printf("\n");
		}
	}
	else
		cursor->steps_next_oper = OP_CODE_SIZE;
	move_cursor(cursor);
}

void	run(t_vm *vm)
{
	t_carriage *cursor;

	while (vm->cursor)
	{
		dump_output(vm);
		vm->cycles++;
		vm->check_to_die++;
		if (vm->logs)
			ft_printf("It is now cycle %zd\n", vm->cycles);
		cursor = vm->cursor;
		while (cursor)
		{
			cursor->pos %= MEM_SIZE;
			cod_oper(vm, cursor);
			if (cursor->cycles_to_cod == 0)
				start_oper(vm, cursor);
			cursor = cursor->next;
		}
		check_map(vm);
	}
}

void	free_vm(t_vm *vm)
{
	t_champ *tmp;

	while (vm->champ_first)
	{
		tmp = vm->champ_first;
		vm->champ_first = vm->champ_first->next;
		free(tmp->exec_cod);
		free(tmp);
		tmp = NULL;
	}
}

int		main(int argc, char **argv)
{
	t_pars	pars;
	t_vm	vm;

	ft_bzero(&vm, sizeof(vm));
	ft_bzero(&pars, sizeof(pars));
	pars.arg = argv + 1;
	pars.index = argc - 1;
	if (argc >= 2)
	{
		pars_arg(&pars, &vm);
		create_arena(&vm);
		create_cursor(&vm);
		player_introduction(&vm);
		run(&vm);
		output_winner(&vm);
	}
	else
		usage();
	exit(0);
}
