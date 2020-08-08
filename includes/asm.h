#ifndef ASSEMBLER_ASM_H

#define ASSEMBLER_ASM_H

# include "../libft/libft.h"
# include <stdio.h>
# include "op.h"
# include <fcntl.h>

# define false 0
# define true 1

//TODO изменить наименования, а то одни и те же

typedef enum      s_arg_type
{
    LABEL,
    INSTRUCTION,
    DIRECT,
    DIRLABEL,
    INDIRECT,
    INDIRLABEL,
    REGISTER
}                 t_types;

//TODO изменить наименования, а то одни и те же

typedef enum    s_operations
{
    live,
    ld,
    st,
    add,
    sub,
    and,
    or,
    xor,
    zjmp,
    ldi,
    sti,
    ffork,
    lld,
    lldi,
    lfork,
    aff
}               t_operations;

/*
 * name - name of player;
 * comment - comment of player;
 * text - all text;
 * split_text - all text divided to array;
 * line - keeping line of parsing;
 * sym - keeping position in line when stopped;
 */

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

/*
 * name - name of operation;
 * args_num - number of arguments;
 * args_type - types of all arguments;
 * op_code - operations code;
 * cycle - are cycles untill performance (цикл до исполнения).
 * specif - description of this type of operation;
 * args_code - is code of type of argument;
 * t_dir_size -  размер типа T_DIR;
 */

typedef struct s_oper
{
    char        name[6];
    char        args_num;
    char        args_type[3];
    char        op_code;
    int         cycle;
    char        specif[37]; //если не используется, удалить
    char        args_code; //если не используется, удалить
    char        t_dir_size; //если не используется, удалить
}               t_oper;


//TODO изменить наименования, а то одни и те же

typedef struct      s_tokens
{
    char            *str;
    int             line;
    int             sym;
    t_types      arg_type;
    t_oper          *oper;
    char            size;
    struct s_tokens *next;
}                   t_tokens;



void        error_print(char *str);
char        *ft_move_text(char *str1, char *str2);

void        ft_gen_parsing(char *file_name);
void        parsing_name_comm(t_all *all);
void        record_name(t_all *all);
int         check_comment(const char* str);
void        record_comment(t_all *all);
void        pass_void(t_all *all);
void        parser(t_all *all);
t_oper      parse_operation(t_all *all, int *i);
int         parse_lbl(int *i, int *lbl_flag, t_oper *op, t_all *all);
#endif //ASSEMBLER_ASM_H
