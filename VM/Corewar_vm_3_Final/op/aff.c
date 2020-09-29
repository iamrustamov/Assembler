/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_aff(t_vm *vm, t_carriage *cursor)
{
	int value;
	int reg;

	cursor->steps_next_oper += OP_ARGS_CODE_SIZE;
	reg = vm->arena[address(cursor)];
	value = cursor->reg[reg - 1];
	cursor->steps_next_oper += REG_S;
	if (vm->aff)
		ft_printf("Aff: %c\n", (char)value);
}
