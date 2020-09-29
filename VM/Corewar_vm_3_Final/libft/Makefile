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

CFILE =	ft_error.c get_next_line.c ft_putchar.c \
        ft_memset.c ft_bzero.c ft_memccpy.c \
        ft_memchr.c ft_memcmp.c ft_memcpy.c \
        ft_memmove.c ft_strlen.c ft_strcpy.c \
        ft_strdup.c ft_strncpy.c ft_strcat.c \
        ft_strncat.c ft_strlcat.c ft_strchr.c \
        ft_strrchr.c ft_strstr.c ft_strnstr.c \
        ft_strcmp.c ft_strncmp.c ft_atoi.c \
        ft_isalpha.c ft_isdigit.c ft_isalnum.c \
        ft_isascii.c ft_isprint.c ft_toupper.c \
        ft_tolower.c ft_memalloc.c ft_memdel.c \
        ft_strnew.c ft_strdel.c ft_strclr.c \
        ft_striter.c ft_striteri.c ft_strmap.c \
        ft_strmapi.c ft_strequ.c ft_strnequ.c \
        ft_strsub.c ft_strjoin.c ft_strtrim.c \
        ft_strsplit.c ft_itoa.c ft_putstr.c \
        ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
        ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
        ft_memlcpy.c ft_itoa_base_sig.c ft_itoa_base_unsig.c \
        ft_intstr.c ft_intlen.c ft_printf/ft_lib_f.c \
        ft_printf/f_frac.c ft_printf/ft_output.c \
        ft_printf/f_get_ent.c ft_printf/ft_output_csp.c \
        ft_printf/f_lst.c ft_printf/ft_output_d.c \
        ft_printf/f_parse.c ft_printf/ft_output_x.c \
        ft_printf/f_putnum.c ft_printf/ft_pars.c \
        ft_printf/f_round.c ft_printf/ft_printf.c \
        ft_printf/f_spec.c ft_printf/ft_prt.c \
        ft_printf/f_sup.c ft_printf/float.c \
        ft_printf/f_sup2.c \

FLAGS = -Wall -Wextra -Werror

OBJ = $(CFILE:.c=.o)

HFILE = libft.h

all: $(NAME)

%.o: %.c libft.h
	@gcc -c $< -o $@ -I $(HFILE)

$(NAME): $(OBJ) libft.h
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all