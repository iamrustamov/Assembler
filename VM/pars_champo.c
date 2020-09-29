/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_champo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	pars_chemp(t_pars *pars, t_vm *vm)
{
	if (!ft_strcmp(ft_strchr(*pars->arg, '\0') - ft_strlen(".cor"), ".cor")
	&& ft_strlen(*(pars->arg)) >= 4)
	{
		pars->id++;
		add_champ(*(pars->arg), pars, vm);
		vm->player_num++;
		pars->arg++;
		pars->index--;
	}
	else
		usage();
}

void	add_champ(char *arg, t_pars *pars, t_vm *vm)
{
	vm->champ->next = (t_champ *)ft_memalloc(sizeof(t_champ));
	pars_cor(arg, pars, vm);
	vm->champions[vm->player_num] = vm->champ;
	vm->champ = vm->champ->next;
}

void	pars_cor(char *arg, t_pars *pars, t_vm *vm)
{
	if ((pars->fd = open(arg, O_RDONLY)) < 0)
		ft_error("invalid file");
	if (pars_bit_4(pars->fd) != COREWAR_EXEC_MAGIC)
		ft_error("invalid magic");
	pars_str_name(pars->fd, vm);
	if (pars_bit_4(pars->fd) != 0)
		ft_error("no null");
	vm->champ->exec_cod_size = pars_bit_4(pars->fd);
	if ((vm->champ->exec_cod_size < 0) ||
	(vm->champ->exec_cod_size > CHAMP_MAX_SIZE))
		ft_error("invalid exec code");
	pars_str_comment(pars->fd, vm);
	if (pars_bit_4(pars->fd) != 0)
		ft_error("no null");
	vm->champ->exec_cod = pars_cod(pars->fd, vm->champ->exec_cod_size);
}

void	pars_str_name(int fd, t_vm *vm)
{
	int	res;

	res = read(fd, vm->champ->name, PROG_NAME_LENGTH);
	if (res == -1 || res < PROG_NAME_LENGTH)
		ft_error("invalid name");
}

void	pars_str_comment(int fd, t_vm *vm)
{
	int	res;

	res = read(fd, vm->champ->comment, COMMENT_LENGTH);
	if (res == -1 || res < COMMENT_LENGTH)
		ft_error("invalid comment");
}
