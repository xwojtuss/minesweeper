COMPILER = cc
CFLAGS = -Wall -Wextra -Werror --pedantic

NAME = minesweeper

SRCS = srcs/main.c srcs/get_next_line.c

OBJECTS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJECTS}
	${COMPILER} ${CFLAGS} $^ -o $@ -I.

%.o: %.c
	${COMPILER} ${CFLAGS} -c $< -o $@ -I.

clean:
	rm -f ${OBJECTS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re