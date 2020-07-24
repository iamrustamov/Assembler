/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 18:02:38 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/03 23:47:11 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void				ft_lstclear(t_list *root)
{
	t_list				*tmp;

	while (root != NULL)
	{
		tmp = root->next;
		free(tmp);
		root = tmp;
	}
}

t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list				*head;
	t_list				*car;

	if (!lst || !f)
		return (NULL);
	car = f(lst);
	head = car;
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (!(car->next = f(lst)))
		{
			ft_lstclear(car);
			return (NULL);
		}
		else
			car = car->next;
	}
	return (head);
}
