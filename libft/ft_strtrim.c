/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:02:40 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/01 15:39:07 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_strtrim(const char *s)
{
	unsigned	int		start;
	unsigned	int		end;
	char				*ptr;
	unsigned	int		print;

	print = 0;
	start = 0;
	if (!s)
		return (0);
	end = ft_strlen(s) - 1;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	if (s[start] == '\0')
		return (ft_strcpy(ft_memalloc(sizeof(char)), ""));
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	if (!(ptr = (char *)malloc(sizeof(char) * (end - start + 2))))
		return (NULL);
	while (print < end - start + 1)
	{
		ptr[print] = s[start + print];
		print++;
	}
	ptr[print] = '\0';
	return (ptr);
}
