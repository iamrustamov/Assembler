/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:04:04 by dpenney           #+#    #+#             */
/*   Updated: 2019/09/25 17:31:14 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	if (len == 0)
		return (0);
	while (len > (i + j) && s1[i] != '\0')
	{
		j = 0;
		while ((s2[j] != '\0') && (s1[i + j] == s2[j]) && (i + j) < len)
			j++;
		if (s2[j] == '\0')
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
