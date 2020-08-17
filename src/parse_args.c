#include "asm.h"
//TODO продебажить правильность функци.
/*
 * This function cleaning strings of arguments of tabs and spaces.
 */
void           		clean_voids(char **str)
{
	int             x;
	int             y;
    char            *res;

	if (str == NULL || *str == NULL)
		return ;
	x = 0;
	while (*str[x] && (*str[x] == ' ' ||
			*str[x] == '\n' || *str[x] == '\t'))
		x++;
	y = ft_strlen(*str) - 1;
	while (x < y && ((*str)[y] == ' ' ||
	        (*str)[y] == '\n' ||
            (*str)[y] == '\t'))
	    y--;
	y = y - x + 1;
	if (!(res = ft_strsub(*str, x, y)))
	    error_printf(NULL, ERROR_ALLOCATE, NULL);
	ft_strdel(str);
	*str = res;
}

int                 check_reg_num(char *str)
{
	int             i;
	int             res;


	i = 0;
	res = 0;
	if (str)
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (ft_isdigit(str[i]))
		{
			if (res > MAX_UINT || (res == NEARLY_MAX_UINT &&
				str[i] >= '5'))
				return (0);
			res = res * 10 + str[i] - 48;
			i++;
		}
		if (str[i] == '\0' && 0 < i)
			return (1);
		else
			return (0);
	}
	return (0);
}

/*
 * Если есть % и :, значит дальше будет метка,
 * метка парсится отдельно.
 * Дальше смотрим - если дальше идут до конца цифры, то отлично.
 */

int                 check_t_dir(char *str)
{
	int             i;

	i = 0;
	if ( str[i] && str[i] == '%')
	{
		i++;
		if (str[i] == ':')
			return (TRUE);
	}
	else if (str[i] != '\0')
	{
		if (str[i] == '-')
			i++;
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] == '\0')
			return (TRUE);
	}
	return (FALSE);
}

int                 check_t_ind(char *str)
{
	int             i;

	i = 0;
	if (str[i] == ':')
	{
		i++;
		if (!ft_strchr(str, ':'))
			return (TRUE);
	}
	else if (str[i] != '\0')
	{
		if (str[i] == '-')
			i++;
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] == '\0')
			return (TRUE);
	}
	return (FALSE);
}

/*
 * Checking arguments by 3 types - T_REG, T_DIR, T_IND(ID);
 */

int                 search_types(char *str)
{
	int             i;
	int             arg_num;

	arg_num = 0;
	i = 0;
	if (str[i] == 'r')
	{
		i++;
		if (str[i] == '-' || str[i] == '+' ||
			!check_reg_num(str))
			return (FALSE);
		arg_num = ft_atoi(str);
		if (arg_num <= REG_NUMBER && arg_num >= 0)
			return (T_REG);
	}
	else if (check_t_dir(str))
		return (T_DIR);
	else if (check_t_ind(str))
		return (T_IND);
	return (WRONG_TYPE)
}

/*
 * Находим тип. Если тип не найден, то вывод ошибки.
 * Когда тип найден, то парсим эти данные в структуру данных t_args.
 * А дальше фигачим в операцию всю инфу.
 */

void                set_types(t_asm *bler, t_operation *oper, char **args)
{
	char            f;
	int             i;
	char            type;

	i = 0;
	while (args[i] != NULL)
	{
		if ((type = search_types(args[i])) == -1)
			error_printf(bler, ERROR_ARGS_TYPE, bler->line);

	}
}

void                parse_args(t_asm *bler, t_operation *oper)
{
	char **args;
	int i;

	i = 0;
	args = ft_strsplit(bler->line + bler->sym, SEPARATOR_CHAR);
	if (!(args))
		error_printf(bler, ERROR_ARGS, bler->line);
	while (args[i])
		clean_voids(&args[i++]);
	set_types(bler, oper, args);
}


