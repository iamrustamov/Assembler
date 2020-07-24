#include "../includes/asm.h"

void        ft_gen_parsing(char *file_name)
{
    int     fd;
    t_all   *all;

    all = (t_all *)ft_memalloc()
    fd = 0;
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
//        error_print()
        exit(-1);
    parse_name();
    parse_comments();
    parse_tokens();
    p
}

int         ft_validation_file(const char *str)
{
    if (ft_strcmp(&str[ft_strlen(str) - 2], ".s"))
    {
        printf("OK.\n");
    }
    return (1);
}

int         main(int argc, char **argv)
{
    if (argc == 2 && ft_validation_file(argv[1]))
    {
        printf("OK..\n");
        ft_gen_parsing(argv[1]);
    }
    return (0);
}
