

#ifndef ASSEMBLER_ASM_H
#define ASSEMBLER_ASM_H

#include <op.h>
#include "stdio.h" // remove it
#include "../libft/libft.h"

typedef struct      s_array
{
    char            arg[3];
}                   t_array;

typedef struct      s_op_list
{
    char            *name;
    char            args_num;
    t_array         args[3];
    char            op_code;
    char            codage;
    char            lbl_size;
}                   t_op_list;

typedef enum
{
    LABEL = 1,
    COMMAND
};

typedef  struct     s_arg
{
    char            *s_val;
    int             n_val;
    char            *args_size;
    char            *type;
    struct s_arg    *next;
}                   t_arg;

typedef  struct         s_operation
{
    char                *name;
    char                *op_code;
    int                 byte;
    t_list              *lbl;
    t_arg               *args;
    struct s_operation  *next;
}                       t_operation;

typedef  struct     s_asm
{
    int             fd;
    char            *files_name;
    char            *name;
    char            *comment;
    char            *line;
    int             line_len;
    int             cor_fd;
    t_operation     *oper;
}                   t_asm;

/*
 * Functions
 */
void                error_printf(t_asm *bler, char *text, char *line);
void                parser(t_asm *bler);
void                parse_name_comm(t_asm *bler);\
void                parse_commands(t_asm *bler);
#endif
