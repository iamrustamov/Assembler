/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	dump_flag(t_pars *pars, t_vm *vm)
{
	if (*(pars->arg + 1) && ft_isdigit(*(pars->arg + 1)[0]) == 1 &&
			pars->index >= 2)
	{
		vm->dump = 1;
		vm->dump_cycles = ft_atoi(*(pars->arg + 1));
		(pars->index) -= 2;
		(pars->arg) += 2;
	}
	else
		usage();
}

void	n_flag(t_pars *pars, t_vm *vm)
{
	int id;

	if (*(pars->arg + 1) && ft_isdigit(*(pars->arg + 1)[0]) == 1 &&
			pars->index >= 3)
	{
		if ((id = ft_atoi(*(pars->arg + 1))) < 1)
			usage();
		if (!ft_strcmp(ft_strchr(*(pars->arg + 2), '\0') - ft_strlen(".cor"),
			".cor") && ft_strlen(*(pars->arg + 2)) >= 4)
		{
			pars->id++;
			add_champ(*(pars->arg + 2), pars, vm);
			vm->champions[vm->player_num]->id = id;
			vm->player_num++;
		}
		else
			usage();
		(pars->index) -= 3;
		(pars->arg) += 3;
	}
	else
		usage();
}

void	aff_flag(t_pars *pars, t_vm *vm)
{
	vm->aff = 1;
	(pars->index) -= 1;
	(pars->arg) += 1;
}

void	live_flag(t_pars *pars, t_vm *vm)
{
	vm->live = 1;
	(pars->index) -= 1;
	(pars->arg) += 1;
}

void	logs_flag(t_pars *pars, t_vm *vm)
{
	vm->logs = 1;
	(pars->index) -= 1;
	(pars->arg) += 1;
}
