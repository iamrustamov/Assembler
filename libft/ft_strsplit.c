/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:51:13 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/03 23:37:03 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_free(char **for_free, size_t count)
{
	size_t			i;

	i = 0;
	while (count > i)
	{
		free(for_free[i]);
		i++;
	}
	free(for_free);
	for_free = NULL;
	return (NULL);
}

static	int			num_word(char const *s, char c)
{
	int				i;
	int				num;

	i = 0;
	num = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			num++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (num);
}

static	char		*ft_memword(char const *s, size_t mem)
{
	char			*ptr;

	if (!(ptr = (char *)malloc(sizeof(char) * mem + 1)))
		return (NULL);
	ptr = ft_strncpy(ptr, s, mem);
	ptr[mem] = '\0';
	return (ptr);
}

static	char		**ft_fill(const char *s, char c, size_t count)
{
	size_t			j;
	size_t			n;
	size_t			i;
	char			**next;

	i = 0;
	n = 0;
	if (!(next = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
			if (!(next[n++] = ft_memword(s + j, i - j)))
			{
				ft_free(next, count);
				return (NULL);
			}
	}
	next[n] = 0;
	return (next);
}

char				**ft_strsplit(char const *s, char c)
{
	size_t			count;

	if (!s || !c)
		return (NULL);
	if (s == NULL)
		return (NULL);
	count = num_word(s, c);
	return (ft_fill(s, c, count));
}
