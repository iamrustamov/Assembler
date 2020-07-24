/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:47:54 by dpenney           #+#    #+#             */
/*   Updated: 2019/09/23 03:15:25 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int					j;

	j = ft_strlen(s);
	if (c == 0)
		return ((char *)s + j);
	while (j >= 0)
	{
		if (s[j] == c)
			return ((char *)s + j);
		else
			j--;
	}
	if (!c && s[j] == '\0')
		return ((char *)s + j);
	return (NULL);
}
