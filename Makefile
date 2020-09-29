# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpenney <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/27 20:30:06 by dpenney           #+#    #+#              #
#    Updated: 2020/09/27 20:30:49 by dpenney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = compiling

COMPL = gcc
CFLAGS = -Wall -Wextra -Werror -I
ASM_DIR = ASM
VM_DIR = ./VM


all: $(NAME)

$(NAME):
		make -C $(ASM_DIR)
		make -C $(VM_DIR)

clean:
		make -C $(ASM_DIR) clean
		make -C $(VM_DIR) clean

fclean: clean
		make -C $(ASM_DIR) fclean
		make -C $(VM_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
