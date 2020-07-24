/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 11:03:51 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/03 20:01:37 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstnum(t_list *alst, size_t num)
{
	size_t		i;

	if (!alst || !num)
		return (NULL);
	if (num == 0)
		return (alst);
	i = 0;
	while (num > i)
	{
		alst = alst->next;
		i++;
	}
	return (alst);
}
