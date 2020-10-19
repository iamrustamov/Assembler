/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_bit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int				pars_bit_4(int fd)
{
	size_t			res;
	unsigned char	buf[4];

	res = read(fd, &buf, 4);
	if (res < 4)
		ft_error("invalid file");
	return (bit(buf, 4, 0));
}

int				bit(const unsigned char *buf, int size, char sign)
{
	int res;
	int i;

	i = 0;
	res = 0;
	while (size--)
	{
		res <<= 8;
		if (sign)
			res |= (unsigned char)buf[i++] ^ 0xFF;
		else
			res |= (unsigned char)buf[i++];
	}
	if (sign)
		res = ~(res);
	return (res);
}

int				bit_args(t_vm *vm, int pos, int size)
{
	int				i;
	char			sign;
	unsigned char	bait[size];

	i = 0;
	while (i != size)
	{
		bait[i++] = vm->arena[(pos++) % MEM_SIZE];
	}
	sign = (char)(bait[0] & 0x80);
	return (bit(bait, size, sign));
}

void			write_bit(t_vm *vm, t_carriage *cursor, int value, int addres)
{
	int addr;

	addr = ((addres % IDX_MOD) + cursor->pos);
	if (addr < 0)
		addr += MEM_SIZE;
	vm->arena[addr % MEM_SIZE] = (unsigned char)((value >> 24) & 0xFF);
	vm->arena[(1 + addr) % MEM_SIZE] = (unsigned char)((value >> 16) & 0xFF);
	vm->arena[(2 + addr) % MEM_SIZE] = (unsigned char)((value >> 8) & 0xFF);
	vm->arena[(3 + addr) % MEM_SIZE] = (unsigned char)(value & 0xFF);
}

unsigned char	*pars_cod(int fd, size_t len)
{
	ssize_t			res;
	unsigned char	*buf;
	unsigned char	b;

	buf = (unsigned char *)ft_memalloc(sizeof(unsigned char) * len);
	res = read(fd, buf, len);
	if (res == -1 || res < (ssize_t)len || read(fd, &b, 1) != 0)
		ft_error("invalid exec code");
	return (buf);
}
