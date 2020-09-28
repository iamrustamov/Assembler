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

int		address(t_carriage *cursor)
{
	int address;

	address = (cursor->pos + cursor->steps_next_oper) % MEM_SIZE;
	if (address < 0)
		address += MEM_SIZE;
	return (address);
}

int		determine_value(unsigned char arg, t_vm *vm, t_carriage *cursor)
{
	int value;
	int addr;

	if (arg == REG_CODE)
	{
		value = cursor->reg[(vm->arena[address(cursor)]) - 1];
		cursor->steps_next_oper += REG_S;
	}
	else if (arg == DIR_CODE)
	{
		value = bit_args(vm, address(cursor),
			g_op_tab[cursor->op_cod - 1].dir_size);
		cursor->steps_next_oper += g_op_tab[cursor->op_cod - 1].dir_size;
	}
	else if (arg == IND_CODE)
	{
		addr = (cursor->pos + (bit_args(vm, address(cursor), 2)
				% IDX_MOD)) % MEM_SIZE;
		if (addr < 0)
			addr += MEM_SIZE;
		value = bit_args(vm, addr, 4);
		cursor->steps_next_oper += IND_S;
	}
	return (value);
}

int		determine_value_lld(unsigned char arg, t_vm *vm, t_carriage *cursor)
{
	int value;
	int addr;

	if (arg == DIR_CODE)
	{
		value = bit_args(vm, address(cursor), 4);
		cursor->steps_next_oper += g_op_tab[cursor->op_cod - 1].dir_size;
	}
	else if (arg == IND_CODE)
	{
		addr = (cursor->pos + bit_args(vm, address(cursor), 2)) % MEM_SIZE;
		if (addr < 0)
			addr += MEM_SIZE;
		value = bit_args(vm, addr, 4);
		cursor->steps_next_oper += IND_S;
	}
	return (value);
}

char	kod_args(unsigned char b, int f)
{
	char res;

	if (f == 0)
		res = (char)((b & 0xC0) >> 6);
	else if (f == 1)
		res = (char)((b & 0x30) >> 4);
	else if (f == 2)
		res = (char)((b & 0xC) >> 2);
	return (res);
}
