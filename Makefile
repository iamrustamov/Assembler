# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpenney <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/27 20:30:06 by dpenney           #+#    #+#              #
#    Updated: 2020/09/29 09:19:05 by doberyn          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
VM = corewar

COMPL = gcc
CFLAGS = -Wall -Wextra -Werror -I
ASM_DIR = ASSEMBLER
VM_DIR = ./VM
NORM = norma

all: $(ASM) $(VM)

$(VM):
		make -C $(VM_DIR)
$(ASM):
		make -C $(ASM_DIR)

$(NORM):
		norminette ./ASSEMBLER/src/*.c
		norminette ./ASSEMBLER/includes/*.h
		norminette ./VM/*.c
		norminette ./VM/*.h

clean:
		make -C $(ASM_DIR) clean
		make -C $(VM_DIR) clean

fclean: clean
		make -C $(ASM_DIR) fclean
		make -C $(VM_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
