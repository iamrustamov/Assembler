# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 22:20:48 by tyasmine          #+#    #+#              #
#    Created: 2020/02/14 22:20:48 by tyasmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../corewar
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = vm.c\
		./check_arena.c\
		./create_arena.c\
		./determine_value.c\
		./output.c\
		./pars_args.c\
		./pars_bit.c\
		./pars_champo.c\
		./pars_flag.c\
		./run_vm.c\
		./op/add.c\
		./op/aff.c\
		./op/and.c\
		./op/fork.c\
		./op/ld.c\
		./op/ldi.c\
		./op/lfork.c\
		./op/live.c\
		./op/lld.c\
		./op/lldi.c\
		./op/or.c\
		./op/st.c\
		./op/sti.c\
		./op/sub.c\
		./op/xor.c\
		./op/zjmp.c

HEADERS = vm.h op.h
OBJ = $(SRC:.c=.o)
LIBFT_HEADER = ./libft/libft.h
LIBFT = ./libft/libft.a
INCLUDES = ./vm.h

all: $(NAME)

%.o: %.c $(INCLUDES) $(LIBFT)
	$(CC) $(FLAGS) -o $@ -c $< -I $(INCLUDES)

$(NAME): $(LIBFT) $(OBJ) $(HEADERS) $(LIBFT_HEADER)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C ./libft

clean:
	rm -f $(OBJ)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY : all clean fclean re

