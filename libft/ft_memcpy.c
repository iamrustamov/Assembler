/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:42:19 by dpenney           #+#    #+#             */
/*   Updated: 2019/09/18 15:13:09 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				a;
	unsigned	char	*temp;
	unsigned	char	*temp2;

	a = 0;
	temp = (unsigned char *)dst;
	temp2 = (unsigned char *)src;
	if (dst == src)
		return (dst);
	while (n > a)
	{
		temp[a] = temp2[a];
		a++;
	}
	return (dst);
}
