/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 11:20:46 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/16 17:04:31 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstsearch(t_list *alst, char *content)
{
	t_list		*curr;

	if (!alst || !content)
		return (NULL);
	curr = alst;
	while (curr->next != NULL)
	{
		if ((ft_strcmp(curr->content, content)) == 0)
			return (curr);
		else
			curr = curr->next;
	}
	return (NULL);
}
