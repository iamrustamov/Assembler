/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 08:13:43 by dpenney           #+#    #+#             */
/*   Updated: 2019/09/30 08:29:24 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstdelstr(t_list **alst)
{
	t_list		*head;
	t_list		*new_head;

	if (!alst || !(*alst))
		return ;
	head = *alst;
	while (head)
	{
		new_head = head->next;
		free(head->content);
		free(head);
		head = new_head;
	}
	*alst = NULL;
}
