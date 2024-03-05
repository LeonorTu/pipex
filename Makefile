NAME = pipex

LIBFT = ./libft/libft.a

SRCS = pipex.c \
		pipex_utils.c

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${SRCS} $(LIBFT)
	@cc $(CFLAGS) $^ -o $@ $(LIBFT)
	@echo "---------Pipex Ready---------"

$(LIBFT):
	@make -C libft/

clean:
	@make clean -C libft
	@rm -rf *.dSYM
	@rm -rf .vscode
	@rm -rf .DS_Store

fclean: clean
	@rm -f ${NAME}
	@make fclean -C libft
	@echo "---------Everything Deleted---------"

re: fclean all

.PHONY: all clean fclean re
