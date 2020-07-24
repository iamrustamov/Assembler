/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:05:27 by dpenney           #+#    #+#             */
/*   Updated: 2019/09/20 22:56:41 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned	char	*ptr_dst;
	unsigned	char	*ptr_src;
	unsigned	char	tmp;

	tmp = (unsigned char)c;
	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	while (n--)
	{
		*ptr_dst++ = *ptr_src++;
		if (tmp == *(ptr_dst - 1))
			return (ptr_dst);
	}
	return (NULL);
}
