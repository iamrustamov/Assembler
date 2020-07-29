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
    int         line;
    int         sym;
}               t_all;

# define false 0
# define true 1

void        error_print(char *str);
char        *ft_move_text(char *str1, char *str2);

void        ft_gen_parsing(char *file_name);
void        parsing_text(t_all *all);
void        record_name(t_all *all);
int         check_comment(const char* str);
void        record_comment(t_all *all);



#endif //ASSEMBLER_ASM_H
