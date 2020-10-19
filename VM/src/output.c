/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	player_introduction(t_vm *vm)
{
	int id;

	id = 1;
	ft_printf("Introducing contestants...\n");
	while (id <= vm->player_num)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			id, vm->champions[id - 1]->exec_cod_size,
			vm->champions[id - 1]->name, vm->champions[id - 1]->comment);
		id++;
	}
}

void	output_winner(t_vm *vm)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",
		vm->champ_live->id, vm->champ_live->name);
	free_vm(vm);
}

void	usage(void)
{
	ft_printf("Usage: ./corewar [-dump <num>] "
		"[-n <num>] [-a] [-live] [-v] <champion.cor> <...>\n");
	exit(0);
}

void	output_arena(unsigned char *arena)
{
	int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.4p : ", i);
		j = 0;
		while (j < 32)
		{
			ft_printf("%.2x ", arena[i + j]);
			j++;
		}
		ft_printf("\n");
		i += 32;
	}
}

void	dump_output(t_vm *vm)
{
	if (vm->dump_cycles == vm->cycles && vm->dump)
	{
		output_arena(vm->arena);
		exit(0);
	}
}
