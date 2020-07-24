/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlastn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 07:56:04 by dpenney           #+#    #+#             */
/*   Updated: 2019/09/30 07:58:15 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstlastn(t_list *head)
{
	t_list		*tmp;

	if (!head)
		return (NULL);
	else
		tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
