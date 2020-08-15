

#ifndef ASSEMBLER_ASM_H
#define ASSEMBLER_ASM_H

#include <op.h>
#include "stdio.h" // remove it
#include "../libft/libft.h"

# define TRUE 1
# define FALSE 0
# define ERROR_LINE "ERROR: This line have not valid parameters\n"
# define ERROR_ARGS "ERROR: This line have not valid arguments\n"

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

typedef enum types
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

typedef struct          s_lbls
{
    char                *str;
    int                 strlen;
    struct s_lbls       *next;
}                       t_lbls;

typedef  struct         s_operation
{
    char                *name;
    int                 op_code; // у него установлено char.
    int                 byte;
    t_lbls              *lbl;
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
    char            *free_line; //TODO эта переменная понадобится, если line до конца не очищается.
    int             sym;
    int             line_len;
    int             cor_fd;
    t_operation     *oper;
}                   t_asm;

/*
 * Functions
 */
void                parser(t_asm *bler);
void                parse_name_comm(t_asm *bler);\
void                parse_commands(t_asm *bler);
t_operation         *init_op_list(t_asm *bler);
void                parse_args(t_asm *bler, t_operation *oper);

int                 check_label(t_asm *bler);
void                add_lbls(t_asm *bler, t_operation *oper);

int                 check_op(t_asm *bler);
void                add_op(t_asm *bler, t_operation *oper);
/*
 * Instruments
 */
void                pass_comments(char *str);
void                pass_voids(t_asm *bler);
void                error_printf(t_asm *bler, char *text, char *line);

#endif
