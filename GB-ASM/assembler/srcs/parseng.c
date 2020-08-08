/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseng.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:48:58 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/15 02:59:55 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		bad_lbl_char_manage(t_all *all, int f, int *incorrect_lbl, int i)
{
    // Если это ":", то просто пропускаем это.
	if (!f && SPLIT[all->i] == LABEL_CHAR)
		++all->i;
	//Если это знаки разделители, комментарии либо что-то подобное, то возв-ем 1.
	else if ((SPLIT[all->i] == SEPARATOR_CHAR
		|| SPLIT[all->i] == ALT_COMMENT_CHAR
		|| SPLIT[all->i] == COMMENT_CHAR || SPLIT[all->i] == '\n'
		|| SPLIT[all->i] == '\t' || SPLIT[all->i] == ' ') && f)
		return (1);
	else if ((*incorrect_lbl = check_label_colon(all, i)))
	{
		ft_error(all, Lexical, Wrong_lchar);
		while (SPLIT[all->i] && SPLIT[all->i] != ',' &&
			SPLIT[all->i] != ' ' && SPLIT[all->i] != '\t')
			++all->i;
	}
	return (1);
}

void	ft_parseng(t_all *all, t_op a, t_operation op)
{
	unsigned	j;
	int			k;

	j = 0;
	k = a.arg_q - 1;
	all->i += ft_strlen((char *)a.cmd);
	while (j < 3)
	{
		SPLIT[all->i] == SEPARATOR_CHAR ? ++all->i : 0;
		if (a.arg_type[j])
			get_argument(all, &k, op, a.arg_type[j]);
		++j;
	}
	last_check(all) ? ft_error(all, Syntactic, Odd_argument) : 0;
}

int		instr_not_found(t_all *all, int *i, int *incorrect_lbl, t_op *a)
{
    //Checkmet это проверка метки.
	checkmet(all, LABEL, 0, incorrect_lbl);
	(*i) = -1;
	quick_pass(all);
	if (!SPLIT[all->i] || SPLIT[all->i] == '\n')
	{
		ft_lstpush(&all->parsing, ft_lstnew_ptr(all->temp));
		all->temp = NULL;
		return (0);
	}
	(*a) = operations(all, i);
	return (1);
}
/*
 * В токенс уже создаёт две структуры данных. t_op и t_tokens.
 *
 * t_op содержит в себе подробности об операции - имя до 6 симв, количестве аргументов,
 * 	массив, в котором хранятся аргументы (их он выделяет 3), код операции, кол-во циклов
 * 	до исполнения, descrip с коротким описанием, код типов аргументов (T_REG, T_DIR, T_IND)
 * 	и dir_size, который содержит размер типа T_DIR.
 *
 * t_token это структура, в которой хранятся:
 * 	Обычный указатель на строку;
 * 	Переменная, которая хранит линию и переменная, которая читает символы.
 * 	t_type, который является enum и хранит в себе LABEL, INSTRUCTION, DIRECT, DIRLABEL, INDIRECT, INDIRLABEL, REGISTER.
 * 	t_operations хранит в себе как в enum константы всех имён операций.
 * 	Далее в size хранится один символ. t_tokens используется как листы, т.к. есть указатель на next.
 *Что делает код?
 * Сначала пропускает все пробелы и табуляции. В operations парсится имя операции.
 */
void	tokens(t_all *all)
{
	t_op		a;
	t_tokens	*token;
	int			i;
	int			size;
	int			incorrect_lbl;

	//пропускаем все пробелы и табуляции.
	quick_pass(all);
	i = -1;
	//парсим операцию
	a = operations(all, &i);
	// Если имя операции не нашлось в строке, то
	if (!a.cmd[0])
	{
		size = all->i; //записывает в size итератор символа, где остановился.
		// а в instr_not_found мы ищём метку (лейбл)
		if (!instr_not_found(all, &i, &incorrect_lbl, &a))
			return ;
	}
	if (!a.cmd[0] && !incorrect_lbl)
		unknown_instr_error(all, &size);
	size = i == live || i == zjmp || i == ffork
			|| i == lfork ? 1 : 2;
	token = ft_newtokens(all, INSTRUCTION, i, (char)size);
	token->str = ft_strsub((char *)a.cmd, 0, ft_strlen((char *)a.cmd));
	ft_tokenspush(&all->temp, token);
	a.cmd[0] ? ft_parseng(all, a, i) : 0;
}

/*
 * через checkform пропускает в цикле символы комментариев # и ;, а также пропускает пробелы и табуляции.
 * И здесь он смотрит - если ещё в сплите остались строки, то через quick_parse пропускает пробелы и табуляции.
 * Далее отправляет в tokens.
 */

void	parseng(t_all *all)
{
	size_t	last_line_len;
//пропускаем все пробелы и табуляции, а также строки с комментариями
//А когда встречаются просто символы, то запоминаем позицию для продолжения чтения
	while (checkform(all))
	{
	    //Если ещё остались строки, то продолжаем
		if (SPLIT)
		{
		    //пропускаем все пробелы и табуляции
			quick_pass(all);
			//приступаем к операциям
			tokens(all);
			all->temp ? ft_lstpush(&all->parsing, ft_lstnew_ptr(all->temp)) : 0;
			all->temp = NULL;
		}
	}
	last_line_len = ft_strlen(SPLIT);
	if (SPLIT[last_line_len - 1] != '\n')
	{
		all->i = last_line_len - 1;
		ft_error(all, Syntactic, No_last_line);
	}
}
