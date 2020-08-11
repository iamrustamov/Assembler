#include "../includes/asm.h"

void            parse_name_comm(t_asm *bler)
{
    int         flags[2];

    ft_bzero(flags, sizeof(int));
    while(get_next_line(bler->fd, &bler->line) > 0 && flags[0] < 2)
    {
        flags[0]++;
    }
}