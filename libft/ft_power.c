/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 08:34:54 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/03 11:29:09 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_power(int n, unsigned int pow)
{
	int			res;

	if (!n || !pow)
		return (0);
	if (pow == 0)
		return (1);
	res = 1;
	while (pow--)
		res = res * n;
	if (res > 2147483647)
		return (0);
	return (res);
}
