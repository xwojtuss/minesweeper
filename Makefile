COMPILER = cc
CFLAGS = -Wall -Wextra -Werror --pedantic -g

NAME = minesweeper

SRCS = srcs/main.c srcs/get_next_line.c srcs/get_next_line_utils.c \
	srcs/allocation.c srcs/errors.c srcs/get_set_type.c

OBJECTS = ${SRCS:.c=.o}

INCLUDE_FOLDER = includes
INCLUDES = includes/minesweeper.h includes/get_next_line.h

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