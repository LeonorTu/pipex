NAME = pipex

LIBFT = ./libft/libft.a

SRCS = pipex.c

CFLAGS = -g #-Wall -Wextra -Werror  #delete -g

all: ${NAME}

${NAME}: ${SRCS} $(LIBFT)
	@cc $(CFLAGS) $^ -o $@ $(LIBFT)
	@echo "---------Pipex Ready---------"

$(LIBFT):
	@make -C libft/

clean:
	@make clean -C libft

fclean: clean
	@rm -f ${NAME} ${NAME_BONUS}
	@make fclean -C libft
	@echo "---------Everything Deleted---------"

re: fclean all

.PHONY: all clean fclean re
