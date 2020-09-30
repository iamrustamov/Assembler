/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	pars_arg(t_pars *pars, t_vm *vm)
{
	vm->champ = (t_champ *)ft_memalloc(sizeof(t_champ));
	vm->champ_first = vm->champ;
	while (pars->index >= 1)
		pars_flag(pars, vm);
	if (vm->player_num < 1 || vm->player_num > MAX_PLAYERS)
		ft_error("wrong number of players");
	add_id(vm);
	add_champions(vm);
	vm->champ_live = vm->champions[vm->player_num - 1];
	vm->cycles_to_die = CYCLE_TO_DIE;
}

void	pars_flag(t_pars *pars, t_vm *vm)
{
	if (!ft_strcmp(*(pars->arg), "-dump"))
		dump_flag(pars, vm);
	else if (!ft_strcmp(*(pars->arg), "-n"))
		n_flag(pars, vm);
	else if (!ft_strcmp(*(pars->arg), "-a"))
		aff_flag(pars, vm);
	else if (!ft_strcmp(*(pars->arg), "-live"))
		live_flag(pars, vm);
	else if (!ft_strcmp(*(pars->arg), "-v"))
		logs_flag(pars, vm);
	else
		pars_chemp(pars, vm);
}

void	add_id(t_vm *vm)
{
	t_champ	*tmp_champ;
	int		id;
	int		flag;
	int 	player;

	flag = 0;
	player = 0;
	id = 1;
	while (player < vm->player_num)
	{
		tmp_champ = vm->champ_first;
		while (tmp_champ)
		{
			if (tmp_champ->id == id)
				flag = 1;
			tmp_champ = tmp_champ->next;
		}
		if (flag == 1)
			id++;
		else
			id = change_id(vm, id);
		flag = 0;
		player++;
	}
}

void	add_champions(t_vm *vm)
{
	int		id;
	int 	player;
	t_champ	*tmp_champ;

	id = 1;
	player = 0;
	while (player < vm->player_num)
	{
		tmp_champ = vm->champ_first;
		while (tmp_champ)
		{
			if (id == tmp_champ->id)
				vm->champions[player] = tmp_champ;
			tmp_champ = tmp_champ->next;
		}
		id++;
		player++;
	}
}

int		change_id(t_vm *vm, int id)
{
	t_champ *tmp_champ;

	tmp_champ = vm->champ_first;
	while (tmp_champ)
	{
		if (tmp_champ->id == 0)
		{
			tmp_champ->id = id;
			return (++id);
		}
		tmp_champ = tmp_champ->next;
	}
	return (id);
}
