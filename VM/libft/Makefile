# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 21:36:03 by tyasmine          #+#    #+#              #
#    Updated: 2019/04/07 21:59:39 by tyasmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFILE =	ft_atoi.c ft_bzero.c ft_isalnum.c \
        ft_isalpha.c ft_isascii.c ft_isdigit.c \
        ft_isprint.c ft_itoa.c ft_memalloc.c \
        ft_memccpy.c ft_memchr.c ft_memcmp.c \
        ft_memcpy.c ft_memdel.c ft_memmove.c \
        ft_memset.c ft_putchar.c ft_putchar_fd.c \
        ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
        ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
        ft_strcat.c ft_strchr.c ft_strclr.c \
        ft_strcmp.c ft_strcpy.c ft_strdel.c \
        ft_strdup.c ft_strequ.c ft_striter.c \
        ft_striteri.c ft_strjoin.c ft_strlcat.c \
        ft_strlen.c ft_strmap.c ft_strmapi.c \
        ft_strncat.c ft_strncmp.c ft_strncpy.c \
        ft_strnequ.c ft_strnew.c ft_strnstr.c \
        ft_strrchr.c ft_strsplit.c ft_strstr.c \
        ft_strsub.c ft_strtrim.c ft_tolower.c \
        ft_toupper.c get_next_line.c ft_intlen.c \
        ft_intstr.c ft_itoa_base_sig.c ft_itoa_base_unsig.c \
        ft_memlcpy.c ft_printf/auxiliary.c ft_printf/dec.c \
        ft_printf/ft_long_math_divider.c ft_printf/ft_long_math_squad.c \
        ft_printf/ft_long_math_substraction.c ft_printf/ft_long_math_summ.c \
        ft_printf/ft_make_man.c ft_printf/ft_print.c \
        ft_printf/ft_print_float.c ft_printf/ft_print_help.c \
        ft_printf/ft_printf.c ft_printf/x.c ft_printf/x_add.c \
        ft_printf/ft_try.c ft_printf/mutual_exclusion.c ft_printf/output.c \
        ft_printf/parser.c ft_printf/simple.c ft_printf/unsigned.c \
        ft_printf/ft_print_nan_inf.c ft_error.c

FLAGS = -Wall -Wextra -Werror

OBJ = $(CFILE:.c=.o)

HFILE = libft.h

all: $(NAME)

%.o: %.c libft.h
	gcc -c $< -o $@ -I $(HFILE)

$(NAME): $(OBJ) libft.h
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all