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
    char        **split_text;
    int         pos[1];
}               t_all;

void        error_print(char *str);
char        *ft_move_text(char *str1, char *str2);

#endif //ASSEMBLER_ASM_H
