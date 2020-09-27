/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 16:39:55 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/16 16:39:57 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_asm	*init_asmb(void)
{
	t_asm	*s;

	if (!(s = (t_asm*)malloc(sizeof(t_asm))))
		ft_error(ERR_MALLOC);
	ft_bzero(s->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(s->comment, COMMENT_LENGTH + 1);
	s->file_name = NULL;
	s->command = NULL;
	s->line = NULL;
	s->flag_a = 0;
	s->flag_b = 0;
	s->prog_size = 0;
	s->new_fd = 0;
	s->fd = 0;
	s->last_line_size = 0;
	s->magic = COREWAR_EXEC_MAGIC;
	return (s);
}

static void		parsing(t_asm *asmb)
{
	get_header(asmb);
	get_commands(asmb);
	if (!asmb->command)
		ft_error(ERR_NOT_ENOUGH_DATA);
	asmb->prog_size = compute_variables(asmb->command);
}

static void		action(t_asm *asmb)
{
	if (asmb->flag_a && !asmb->flag_b)
		show_bot(asmb, asmb->command);
	else if (asmb->flag_b && !asmb->flag_a)
		read_binary(asmb);
	else if (asmb->flag_b && asmb->flag_a)
		ft_error(ERR_FLAGS);
	else
		create_binary(asmb, asmb->command);
}

void            		print_operations(t_command *command)
{
	t_command    *oper;
	int          i = 1;
	t_arg     *args;

	oper = command;
	args = oper->args;
	ft_printf("\nString: \n\n");
	ft_printf("Operation name: %s\n", oper->name);
	ft_printf("Operation size: %d byte.\n", oper->bytes);
	ft_printf("Code type size: %d byte.\n", oper->opcode);
	ft_printf("OPCODE: %.2x.\n", oper->opcode);
	ft_printf("addr:\n");
	if (oper->labels)
		ft_printf("Label name: %s\n", (char *)oper->labels->content);
	else
		ft_printf("\n");
	while (args)
	{
		ft_printf("ARG #%d ", i);
		if (args->flag == UINT_VAL)
			ft_printf("Value: %lld\n", args->num_value);
		else if (args->flag == STRING_VAL)
			ft_printf("Value: %s\n", args->str_value);
		if (args->type == T_REG)
			ft_printf("                Type:%s", "T_REG");
		else if (args->type == T_DIR)
			ft_printf("                Type:%s", "T_DIR");
		else if (args->type == T_IND)
			ft_printf("                Type:%s", "T_IND");
		ft_printf("\nARG SIZE: %d byte\n", args->arg_size);
		args = args->next;
		i++;
		ft_printf("\n");
	}
	ft_printf("\n--------------------------------------\n");

}

int				main(int ac, char **av)
{
	t_asm	*asmb;

	if (ac == 1)
		ft_putstr("Usage: ./asm [-a, -b] <file>\n    \
-a <file.s>   : Instead of creating a .cor file, outputs a \
stripped and annotated version of the code to the standard output.\n    \
-b <file.cor> : Disassembler for binary .cor file.\n");
	else
	{
		asmb = init_asmb();
		check_argvs(asmb, av, ac);
		if (!asmb->file_name ||
			(asmb->fd = open(asmb->file_name, O_RDONLY)) < 0 ||
			read(asmb->fd, 0, 0) == -1)
		{
			ft_printf("Can't read source file %s\n", asmb->file_name);
			exit(0);
		}
		norm_file_name(&asmb->file_name);
		(!asmb->flag_b) ? parsing(asmb) : 0;
		action(asmb);
		close(asmb->fd);
	}
	return (0);
}
