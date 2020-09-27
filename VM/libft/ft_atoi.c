/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:03:14 by tyasmine          #+#    #+#             */
/*   Updated: 2019/12/19 18:35:06 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	eror2(void)
{
	ft_putstr("Error\n");
	exit(1);
}

int		ft_atoi(const char *str)
{
	long long int i;
	long long int sign;
	long long int res;

	i = 0;
	sign = 0;
	res = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	(str[i] == '-') ? sign = 1 : (0);
	(str[i] == '+' || str[i] == '-') ? i++ : (0);
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	(res > INT_MAX || i > 10) ? eror2() : 0;
	if (sign == 1)
		return ((int)-res);
	else
		return ((int)res);
}
