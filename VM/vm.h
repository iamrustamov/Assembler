/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#             */
/*   Updated: 2020/02/14 22:20:52 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft/libft.h"
# include "op.h"
# include <stdio.h>
# include <stdbool.h>

# define OP_CODE_SIZE	    1
# define OP_ARGS_CODE_SIZE	2

# define REG_S				1
# define IND_S				2

# define REG				1
# define DIR				2
# define IND				3

typedef struct			s_champ
{
	int					id;
	char				name[PROG_NAME_LENGTH];
	char				comment[COMMENT_LENGTH];
	int					exec_cod_size;
	unsigned char		*exec_cod;
	struct s_champ		*next;
}						t_champ;

typedef struct			s_carriage
{
	unsigned int		id;
	char				carry;
	unsigned char		op_cod;
	ssize_t				live_last_cycl;
	int					cycles_to_cod;
	int					pos;
	unsigned int		steps_next_oper;
	int					reg[REG_NUMBER];
	unsigned char		op_args[3];
	struct s_carriage	*next;
}						t_carriage;

typedef struct			s_vm
{
	unsigned char		arena[MEM_SIZE];
	t_champ				*champions[MAX_PLAYERS];
	t_champ				*champ;
	t_champ				*champ_first;
	t_champ				*champ_live;
	t_carriage			*cursor;
	t_carriage			*prev;
	size_t				cursor_num;
	size_t				player_num;
	ssize_t				cycles;
	size_t				live_num_to_die;
	ssize_t				cycles_to_die;
	ssize_t				check_to_die;
	size_t				checks;
	ssize_t				dump_cycles;
	unsigned int		cursor_id;
	int					logs;
	int					dump;
	int					live;
	int					aff;
}						t_vm;

typedef struct			s_pars
{
	int					fd;
	int					id;
	int					index;
	char				**arg;
}						t_pars;

typedef struct			s_op
{
	unsigned char		arg;
	unsigned char		args[3][3];
	unsigned int		cycles_exec;
	char				cod_typ_args;
	unsigned char		dir_size;
	void				(*func)(t_vm	*vm, t_carriage *cursor);
}						t_op;

int						bit(const unsigned char *buf, int size, char sign);
int						bit_args(t_vm	*vm, int pos, int size);
int						address(t_carriage *cursor);
void					write_bit(t_vm	*vm, t_carriage *cursor,
					int value, int addres);
int						determine_value(unsigned char arg, t_vm	*vm,
					t_carriage *cursor);
t_carriage				*copy_cursor(int pos, t_carriage *cursor, t_vm	*vm);
int						determine_value_lld(unsigned char arg,
					t_vm	*vm, t_carriage *cursor);
t_carriage				*copy_cursor_lfork(int pos,
					t_carriage *cursor, t_vm	*vm);
void					usage(void);
int						pars_bit_4(int fd);
void					pars_str_name(int fd, t_vm *vm);
void					pars_str_comment(int fd, t_vm *vm);
unsigned char			*pars_cod(int fd, size_t len);
void					pars_cor(char *arg, t_pars *pars, t_vm *vm);
void					add_champ(char *arg, t_pars *pars, t_vm *vm);
void					pars_chemp(t_pars *pars, t_vm *vm);
void					n_flag(t_pars *pars, t_vm *vm);
void					aff_flag(t_pars *pars, t_vm *vm);
void					live_flag(t_pars *pars, t_vm *vm);
void					dump_flag(t_pars *pars, t_vm *vm);
void					logs_flag(t_pars *pars, t_vm *vm);
void					pars_flag(t_pars *pars, t_vm *vm);
int						change_id(t_vm *vm, int id);
void					add_id(t_vm *vm);
void					add_champions(t_vm	*vm);
void					pars_arg(t_pars	*pars, t_vm	*vm);
void					create_arena(t_vm	*vm);
void					add_to_start(t_carriage **list, t_carriage *new);
t_carriage				*add_new_karet(t_vm	*vm, int pos, int id);
void					create_cursor(t_vm	*vm);
void					player_introduction(t_vm *vm);
char					kod_args(unsigned char b, int f);
void					cod_oper(t_vm	*vm, t_carriage *cursor);
void					args_typ(t_vm	*vm, t_carriage *cursor);
unsigned int			arg_size(unsigned char arg, t_carriage *cursor);
unsigned int			step_by_step(t_carriage *cursor);
int						valid_args(t_vm	*vm, t_carriage *cursor);
void					move_cursor(t_carriage *cursor);
void					start_oper(t_vm	*vm, t_carriage *cursor);
t_carriage				*remove_carriage(t_vm *vm, t_carriage	*cursor);
void					delete_cursor(t_vm *vm);
void					check_map(t_vm *vm);
void					output_arena(unsigned char *arena);
void					dump_output(t_vm *vm);
void					run(t_vm *vm);
void					free_vm(t_vm *vm);
void					output_winner(t_vm *vm);
int						main(int argc, char **argv);

void					op_live(t_vm *vm, t_carriage *cursor);
void					op_ld(t_vm *vm, t_carriage *cursor);
void					op_st(t_vm *vm, t_carriage *cursor);
void					op_add(t_vm *vm, t_carriage *cursor);
void					op_sub(t_vm *vm, t_carriage *cursor);
void					op_and(t_vm *vm, t_carriage *cursor);
void					op_or(t_vm *vm, t_carriage *cursor);
void					op_xor(t_vm *vm, t_carriage *cursor);
void					op_zjmp(t_vm *vm, t_carriage *cursor);
void					op_ldi(t_vm *vm, t_carriage *cursor);
void					op_sti(t_vm *vm, t_carriage *cursor);
void					op_fork(t_vm *vm, t_carriage *cursor);
void					op_lld(t_vm *vm, t_carriage *cursor);
void					op_lldi(t_vm *vm, t_carriage *cursor);
void					op_lfork(t_vm *vm, t_carriage *cursor);
void					op_ff(t_vm *vm, t_carriage *cursor);

t_op g_op_tab[16] =
{
	{1, {{DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 10, 0, 4, &op_live},
	{2, {{DIR, IND, 0}, {REG, 0, 0}, {0, 0, 0}}, 5, 1, 4, &op_ld},
	{2, {{REG, 0, 0}, {IND, REG, 0}, {0, 0, 0}}, 5, 1, 4, &op_st},
	{3, {{REG, 0, 0}, {REG, 0, 0}, {REG, 0, 0}}, 10, 1, 4, &op_add},
	{3, {{REG, 0, 0}, {REG, 0, 0}, {REG, 0, 0}}, 10, 1, 4, &op_sub},
	{3, {{REG, DIR, IND}, {REG, IND, DIR}, {REG, 0, 0}}, 6, 1, 4, &op_and},
	{3, {{REG, IND, DIR}, {REG, IND, DIR}, {REG, 0, 0}}, 6, 1, 4, &op_or},
	{3, {{REG, IND, DIR}, {REG, IND, DIR}, {REG, 0, 0}}, 6, 1, 4, &op_xor},
	{1, {{DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 20, 0, 2, &op_zjmp},
	{3, {{REG, DIR, IND}, {DIR, REG, 0}, {REG, 0, 0}}, 25, 1, 2, &op_ldi},
	{3, {{REG, 0, 0}, {REG, DIR, IND}, {DIR, REG, 0}}, 25, 1, 2, &op_sti},
	{1, {{DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 800, 0, 2, &op_fork},
	{2, {{DIR, IND, 0}, {REG, 0, 0}, {0, 0, 0}}, 10, 1, 4, &op_lld},
	{3, {{REG, DIR, IND}, {DIR, REG, 0}, {REG, 0, 0}}, 50, 1, 2, &op_lldi},
	{1, {{DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 1000, 0, 2, &op_lfork},
	{1, {{REG, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 2, 1, 4, &op_aff},
};

#endif
