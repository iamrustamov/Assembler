/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:18:01 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/16 16:02:55 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/asm.h"

void		check_file(t_asm *bler, char *str)
{
	bler->files_name = ft_strsub(str, 0, ft_strlen(str) - 2);
	if (!bler->files_name)
		error_printf(bler, "Error: Can't to read name of the file\n", NULL);
	bler->fd = open(str, O_RDONLY);
	if (bler->fd < 0)
		error_printf(bler, "Error: Can't to open this file\n", NULL);
	if (read(bler->fd, 0, 0) == -1)
		error_printf(bler, "Error: Can't to read this file\n", NULL);
}

void		check_extension(const char *str)
{
	if (ft_strcmp(&str[ft_strlen(str) - 2], ".s") == 0)
		return ;
	error_printf(NULL, ERROR_FILE_EXTENSION, NULL);
}

/*
** TODO нормировать headers
** TODO сделать общий мейкфайл
** TODO проверить по чекерам
** TODO проверить на правильную компиляцию.
 * FIXME не удаляется объек-файл parse_instruments.
 * FIXME Нужно чтоб готовую программу вывес на главную директорию, а не оставлял в папке ASM
* FIXME удалить папку ASM/rock
*/

int			main(int argc, char **argv)
{
	t_asm	bler;

	ft_bzero(&bler, sizeof(bler));
	if (argc == 1 || argc > 2)
		error_printf(&bler, ERROR_USAGE, NULL);
	check_extension(argv[1]);
	check_file(&bler, argv[1]);
	parser(&bler);
	recorder(&bler);
	clear_bler(&bler);
	exit(0);
}
