/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:05:38 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/03 16:48:38 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	char				*mem;
	size_t				i;

	if (size == SIZE_MAX)
		return (NULL);
	i = 0;
	mem = malloc(size);
	if (mem == NULL)
		return (NULL);
	else
		while (size > i)
		{
			mem[i] = 0;
			i++;
		}
	return (mem);
}
