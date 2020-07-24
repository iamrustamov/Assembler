/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:21:28 by dpenney           #+#    #+#             */
/*   Updated: 2019/09/21 19:33:13 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned	char	*ptr_dst;
	unsigned	char	*ptr_src;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (dst <= src)
	{
		while (len--)
			*ptr_dst++ = *ptr_src++;
		return (dst);
	}
	else
	{
		ptr_dst = ptr_dst + len - 1;
		ptr_src = ptr_src + len - 1;
		while (len--)
			*ptr_dst-- = *ptr_src--;
		return (dst);
	}
}
