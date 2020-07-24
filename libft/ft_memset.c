/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oformi_i_uznay_ft_memset.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:10:23 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/03 12:56:15 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;
	size_t			i;

	i = 0;
	temp = (unsigned char *)b;
	while (len > i)
	{
		temp[i] = c;
		i++;
	}
	return (b);
}
