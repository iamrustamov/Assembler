/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oformi_ft_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:07:20 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/03 23:57:39 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_over(long long int res, int sym)
{
	if (res < 0 && sym == 1)
		return (-1);
	else if (res < 0 && sym == -1)
		return (0);
	return (1);
}

int					ft_atoi(const char *str)
{
	size_t					i;
	int						sym;
	long long int			res;

	i = 0;
	sym = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		sym = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if (ft_over(res, sym) <= 0)
		return (ft_over(res, sym));
	return (res * sym);
}
