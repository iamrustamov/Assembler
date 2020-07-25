#ifndef ASSEMBLER_ASM_H

#define ASSEMBLER_ASM_H

# include "../libft/libft.h"
# include <stdio.h>
# include "op.h"
# include <fcntl.h>

typedef struct s_all
{
    int         fd;
    char        *name;
    char        *comment;
    char        *text;
}               t_all;

void        error_print(void);
char        *ft_move_text(char *str1, char *str2);

#endif //ASSEMBLER_ASM_H
