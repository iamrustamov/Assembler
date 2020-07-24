/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 20:56:57 by dpenney           #+#    #+#             */
/*   Updated: 2019/09/23 03:12:16 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t		i;

	i = 0;
	while (src[i] != '\0' && 0 < len)
	{
		dst[i] = src[i];
		i++;
		len--;
	}
	while (0 < len)
	{
		dst[i] = '\0';
		i++;
		len--;
	}
	return (dst);
}
