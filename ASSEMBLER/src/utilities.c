/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:22:18 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/15 06:55:50 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			check_end_line(t_asm *bler)
{
	char		buff[bler->line_len + 1];
	int			i;

	i = 0;
	ft_bzero(buff, bler->line_len + 1);
	if ((lseek(bler->fd, -bler->line_len, SEEK_CUR)) <= 0)
		error_printf(bler, NULL, NULL);
	read(bler->fd, &buff, bler->line_len);
	while (buff[i] != '\0')
	{
		if (buff[i] == COMMENT_CHAR || buff[i] == ALT_COMMENT_CHAR)
			break ;
		else if (buff[i] == ' ' || buff[i] == '\t')
			i++;
		else
		{
			if (buff[ft_strlen(buff) - 1] == '\n')
				break ;
			else
				error_printf(bler, ERROR_END_LINE, NULL);
		}
	}
}

void			pass_voids(t_asm *bler)
{
	if (bler->line)
		while (bler->line[bler->sym] && (' ' == bler->line[bler->sym]
				|| bler->line[bler->sym] == '\t'))
			bler->sym++;
}

/*
** Пропускаем все разделители(пробелы и табы)
*/

void			pass_delimetr(t_data *data)
{
	while ((*data->buff == ' ' || *data->buff == '\t') && *data->buff != '\0')
		data->buff++;
}
