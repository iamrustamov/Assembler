#include "asm.h"

void           		clean_voids(char **str)
{
	int             x;
	int             y;
	int             z;

	if (str == NULL || *str == NULL)
		return ;
	x = 0;
	y = 0;
	while (*str[x] && (*str[x] == ' ' ||
			*str[x] == '\n' || *str[x] == '\t'))
		x++;
	y = ft_strlen(*str) - 1;

}

void                parse_args(t_asm *bler, t_operation *oper)
{
	char **args;
	int i;

	i = 0;
	args = ft_strsplit(bler->line + bler->sym, SEPARATOR_CHAR);
	if (!(args))
		error_printf(bler, ERROR_ARGS, bler->line);
	while (args[i++])
		clean_voids(args[i]);
}


