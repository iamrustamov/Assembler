#include "../includes/asm.h"

int         ft_validation_file(const char *str)
{
    if (ft_strcmp(&str[ft_strlen(str) - 2], ".s"))
        return (0);
    return (1);
}

int         main(int argc, char **argv)
{
    if (argc == 2)
    {
        ft_validation_file(argv[1]);
        ft_gen_parsing(argv[1]);
    }
    return (0);
}
