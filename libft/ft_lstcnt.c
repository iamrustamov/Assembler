/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 11:03:28 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/17 14:17:59 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_lstcnt(t_list *head)
{
	int			i;
	t_list		*link;

	if (!head)
		return (1);
	i = 0;
	link = head;
	while (link)
	{
		link = link->next;
		i++;
	}
	return (i);
}
