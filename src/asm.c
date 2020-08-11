//
// Created by Duram Penney on 8/11/20.
//

#include <fcntl.h>
#include "../includes/asm.h"

void            check_file(t_asm *bler, char *str)
{
    bler->files_name = ft_strdup(str);
    if (!bler->files_name)
        error_printf(bler, "Error: Can't to read name of the file\n", NULL);
    bler->fd = open(bler->files_name, O_RDONLY);
    if (bler->fd < 0)
        error_printf(bler, "Error: Can't to open this file\n", NULL);
    if (read(bler->fd, 0, 0) == -1)
        error_printf(bler, "Error: Can't to read this file\n", NULL);
}

//TODO сделать проверку на *.s расширение.

int             main(int argc, char **argv)
{
    t_asm       bler;
    if (argc == 1 || argc > 2)
        error_printf(&bler, "Error\n", NULL);
    check_file(&bler, argv[1]);
    parser(&bler);
}