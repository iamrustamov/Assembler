/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <dpenney@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 06:18:01 by dpenney           #+#    #+#             */
/*   Updated: 2020/09/29 11:13:56 by doberyn          ###   ########.fr       */
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
	error_printf(NULL, ERR_FILE_EXT, NULL);
}

/*
** TODO проверить по чекерам
** TODO проверить на правильную перекомпиляцию Makefile.
** FIXME не удаляется объек-файл parse_instruments.
*/

int			main(int argc, char **argv)
{
	t_asm	bler;

	ft_bzero(&bler, sizeof(bler));
	if (argc == 1 || argc > 2)
		error_printf(&bler, "Usage: ./asm [-a] <sourcefile.s>\n"\
							"Instead of creating a .cor file,"\
							"outputs a stripped and annotated version"\
							"of the code to the standard output\n", NULL);
	check_extension(argv[1]);
	check_file(&bler, argv[1]);
	parser(&bler);
	recorder(&bler);
	clear_bler(&bler);
	exit(0);
}
