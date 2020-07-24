/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doing_ft_strlcat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:06:18 by dpenney           #+#    #+#             */
/*   Updated: 2019/09/23 03:13:38 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		c;

	i = 0;
	j = 0;
	c = 0;
	while (dst[i])
		i++;
	while (src[j])
		j++;
	if (size <= i)
		j = j + size;
	else
		j = j + i;
	while (src[c] != '\0' && i + 1 < size)
	{
		dst[i] = src[c];
		c++;
		i++;
	}
	dst[i] = '\0';
	return (j);
}
