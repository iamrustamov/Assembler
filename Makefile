asm := ASSEMBLER

corewar := VM

NORM = norm

.PHONY: all $(asm) $(corewar) clean fclean re

all: $(asm) $(corewar)

$(asm):
	$(MAKE) all --no-print-directory -C $(asm)

$(corewar):
	$(MAKE) all --no-print-directory -C $(corewar)

$(NORM):
		norminette ./ASSEMBLER/src/*.c
		norminette ./ASSEMBLER/includes/*.h
		norminette ./ASSEMBLER/libft/*.c
		norminette ./ASSEMBLER/libft/ft_printf/*.c
		norminette ./ASSEMBLER/libft/ft_printf/*.h
		norminette ./ASSEMBLER/libft/ftoa/*.c
		norminette ./ASSEMBLER/libft/ftoa/*.h
		norminette ./ASSEMBLER/libft/includes/*.h
		norminette ./VM/src/*.c
		norminette ./VM/includes/*.h
		norminette ./VM/libft/ft_printf/*.c
		norminette ./VM/libft/ft_printf/*.h
		norminette ./VM/libft/*.h
		norminette ./VM/libft/*.c

clean:
	$(MAKE) clean --no-print-directory -C $(asm)
	$(MAKE) clean --no-print-directory -C $(corewar)

fclean:
	$(MAKE) fclean --no-print-directory -C $(asm)
	$(MAKE) fclean --no-print-directory -C $(corewar)


re: fclean all