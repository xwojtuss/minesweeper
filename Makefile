COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = minesweeper

SRCS = srcs/main.c srcs/allocation.c srcs/errors.c \
		srcs/get_set_type.c srcs/print.c srcs/generate_map.c \
		srcs/parsing.c srcs/reveal.c

OBJECTS = ${SRCS:.c=.o}

INCLUDE_FOLDER = includes
INCLUDES = includes/minesweeper.h

all: ${NAME}

${NAME}: ${OBJECTS}
	${COMPILER} ${CFLAGS} $^ -o $@ -I${INCLUDE_FOLDER}

%.o: %.c ${INCLUDES}
	${COMPILER} ${CFLAGS} -c $< -o $@ -I${INCLUDE_FOLDER}

clean:
	rm -f ${OBJECTS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
