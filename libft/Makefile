NAME = libft.a

SRCS = $(wildcard *.c) $(wildcard get_next_line/*.c)

CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

all: ${NAME}

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	ar rcs $@ $^

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
