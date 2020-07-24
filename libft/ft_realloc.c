/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 11:24:48 by dpenney           #+#    #+#             */
/*   Updated: 2019/10/03 12:26:32 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_realloc(void *ptr, size_t size)
{
	char		*n_ptr;

	if (!size)
		return (ptr);
	if (!(n_ptr = ft_memalloc((size))))
		return (NULL);
	n_ptr = ft_strcpy(n_ptr, ptr);
	ft_memdel(&ptr);
	return (n_ptr);
}
