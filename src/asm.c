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

/*TODO провести по двум чекерам в FAQ 21
** FIXME Daler, Bekha, игрок mat.s имеет несколько ошибок. Совместно разобрать. 
** Когда его ошибки исправляешь, то наш говорит, что размер файла превышает размер игрока, а оригиналы продолжают работать.
** TODO Провести тест на валидные файлы.
**
** FIXME Daler, есть различие в бинарных файлах с игроком Death.s из vm_champs/champs.
** FIXME Daler, имя игрока barriere.s парсит с ошибкой, хотя там все норм. оригинал работает.
** FIXME Binary files 111111.cor and ./vm_champs/champs/slider2.cor differ
*/

int			main(int argc, char **argv)
{
    t_asm	bler;

	ft_bzero(&bler, sizeof(bler));
	if (argc == 1 || argc > 2)
		error_printf(&bler, "Error\n", NULL);
	check_extension(argv[1]);
	check_file(&bler, argv[1]);
	parser(&bler);
	recorder(&bler);
	clear_bler(&bler);
	exit(0);
}
