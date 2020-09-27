/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 21:44:37 by tyasmine          #+#    #+#             */
/*   Updated: 2019/12/19 18:45:49 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

# define BUFF_SIZE 16
# define MAX_FD 4096

typedef	union
{
	long double			i;
	short				c[5];
}						t_un;

typedef struct			s_hex
{
	char				*str;
	int					size;
	int					prlen;
	int					shlen;
}						t_hex;

typedef struct			s_uns
{
	unsigned long long	data;
	char				*str;
	int					len;
	char				sign;
	char				*tmp;
}						t_uns;

typedef struct			s_sig
{
	long long int		data;
	char				*str;
	int					len;
	char				sign;
}						t_sig;

typedef struct			s_flags
{
	int					plus;
	int					sharp:1;
	int					zero:1;
	int					space;
	int					minus:1;
}						t_flags;

typedef struct			s_iterators
{
	int					g;
	int					i;
	int					count;
	int					save;
}						t_iterators;

typedef struct			s_base
{
	const char			*str;
	va_list				arg;
}						t_base;

typedef struct			s_data
{
	int					percent;
	int					width;
	int					dot:1;
	int					prec;
	int					w:1;
	int					length;
	char				type;
	int					sign;
	t_flags				fl;
	t_base				bs;
	t_iterators			it;
}						t_data;

void					ft_error(char *str);
int						get_next_line(const int fd, char **line);
void					ft_putchar(char c);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
							size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
size_t					ft_strlen(const char *s);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strdup(const char *s1);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
							char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char *s, int c);
char					*ft_itoa(int n);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putnbr_c(int n, t_data *new);
int						ft_print_float(t_data *new);
int						*ft_long_math_divider(int *num, int *div, int acc,
							int numb_of_zero);
int						*ft_long_math_squad(int squad, int acc);
int						*ft_long_math_substraction(int *a, int *b, int acc);
int						*ft_long_math_summ(int *a, int *b, int acc);
int						print_before_dot(int *rez, t_data *new, int *rez_celoe);
int						print_after_dot(int *rez, t_data *new, int j);
int						make_man(int man[], int por, t_data *new);
int						*ft_first_try(int **temp, int **div, int acc);
int						*ft_second_try(int **temp, int **div, int acc);
int						*ft_third_try(int **num, int **temp, int acc);
int						*ft_trying_four(int **num, int *rez);
int						ft_print_inf(t_data *new);
int						ft_print_nan(t_data *new);
int						ft_get_size_f(t_data *new, int j);
void					print_before_dot_help(int *rez_celoe, t_data *new,
							int *rez, int j);
void					ft_print_after(t_data *new, int len);
void					ft_putchar_1(t_data *new);
void					ft_type_conversion_signed(t_sig *sig, t_data *new);
void					ft_print_dec(t_data *new);
void					ft_print_c(t_data *new);
void					ft_print_s(t_data *new);
void					ft_print_p(t_data *new);
void					ft_print_percent(t_data *new);
void					ft_leveling(int count, char c, t_data *new);
void					ft_precision(char sign, int len, t_data *new);
char					ft_width(char sign, int len, t_data *new);
void					ft_type_conversion_unsigned(t_uns *uns, t_data *new);
void					ft_print_o(t_data *new);
void					ft_print_u(t_data *new);
void					ft_type_conversion_unsigned(t_uns *uns, t_data *new);
void					ft_print_o(t_data *new);
void					ft_print_u(t_data *new);
void					ft_putstr_precision(char *str, int len, t_data *new);
void					ft_putchar_space(char c, t_data *new);
void					ft_putchar_c(char c, t_data *new);
void					ft_putstr_c(char *s, t_data *new);
void					ft_mutual_exclusion_prec(int len, t_data *new);
void					ft_mutual_exclusion_width(int len, t_data *new);
void					ft_mutual_exclusion(t_data *new, long long data,
							char c);
int						ft_get_size(t_uns *uns, t_data *new);
char					*ft_precision_x(int len, char *str, t_data *new);
char					*ft_sharp_x(int len, char *str, t_data *new);
char					*ft_width_x(int len, char *str, t_data *new);
char					*ft_add_x(int len, char *str, char *dst, t_data *new);
char					*ft_upper(char *str);
void					ft_formating_x(t_uns *uns, t_data *new);
void					ft_print_x(t_data *new);
int						ft_structuring(t_data *new);
void					ft_flags(t_data *new);
int						ft_get_number(t_data *new);
void					ft_get_length(t_data *new);
void					ft_l_or_h(int l, int h, int big_l, t_data *new);
void					ft_structure_cleaning(t_data *new);
void					ft_determination(t_data *new);
void					ft_start(const char *format, t_data *new);
int						ft_vprintf(const char *format, t_data *new);
int						ft_printf(const char *format, ...);
void					*ft_memlcpy(void *dst, const void *src, size_t n,
							int pos);
char					*ft_itoa_base_sig(long long value, int base);
char					*ft_itoa_base_unsig(unsigned long long value, int base);
int						*ft_intstr(int size);
size_t					ft_intlen(long long data);
void					eror2(void);

#endif
