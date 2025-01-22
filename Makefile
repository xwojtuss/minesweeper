SHELL := /bin/bash
COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = minesweeper

SRCS = srcs/main.c srcs/allocation.c srcs/errors.c srcs/generate_map.c \
		srcs/print.c srcs/leaderboard.c srcs/start_game.c \
		srcs/parsing.c srcs/reveal.c \
		srcs/get_type.c srcs/set_type.c

OBJECTS = ${SRCS:.c=.o}

INCLUDE_FOLDER = includes
INCLUDES = includes/minesweeper.h

INVALID_MAPS = ${wildcard maps/invalid/*}
VALID_MAPS = ${wildcard maps/valid/*}

TEST_WAIT = false

all: ${NAME}

${NAME}: ${OBJECTS}
	${COMPILER} ${CFLAGS} $^ -o $@ -I${INCLUDE_FOLDER}

%.o: %.c ${INCLUDES}
	${COMPILER} ${CFLAGS} -c $< -o $@ -I${INCLUDE_FOLDER}

test_f_option:
	@echo -e "\033[1mUruchamianie testów negatywnych z opcją -f:\033[0m"
	@for MAP in ${INVALID_MAPS}; do \
		echo -e "\nTestowanie map: $$MAP"; \
		valgrind --log-file=valgrind.log ./${NAME} -f $$MAP; \
		if ! grep -h --color=auto "All heap blocks were freed -- no leaks are possible" valgrind.log; then \
			echo "Pamięć nie została zwolniona dla: $$MAP"; \
			exit 1; \
		fi; \
		if grep -h --color=auto "ERROR SUMMARY: [^0]" valgrind.log; then \
			echo "Błędy dla mapy: $$MAP"; \
			exit 1; \
		fi; \
		if [ "${TEST_WAIT}" = "true" ]; then \
			read -n 1 -s; \
		fi; \
	done

	@echo -e "\033[1mUruchamianie testów ogólnych z opcją -f:\033[0m"
	@for MAP in ${VALID_MAPS}; do \
		echo -e "\nTestowanie map: $$MAP"; \
		valgrind --log-file=valgrind.log ./${NAME} -f $$MAP; \
		if ! grep -h --color=auto "All heap blocks were freed -- no leaks are possible" valgrind.log; then \
			echo "Pamięć nie została zwolniona dla: $$MAP"; \
			exit 1; \
		fi; \
		if grep -h --color=auto "ERROR SUMMARY: [^0]" valgrind.log; then \
			echo "Błędy dla mapy: $$MAP"; \
			exit 1; \
		fi; \
		if [ "${TEST_WAIT}" = "true" ]; then \
			read -n 1 -s; \
		fi; \
	done

test_stdin:
	@echo -e "\033[1mUruchamianie testów negatywnych jako stdin:\033[0m"
	@for MAP in ${INVALID_MAPS}; do \
		echo -e "\nTestowanie map: $$MAP"; \
		cat $$MAP | valgrind --log-file=valgrind.log ./${NAME}; \
		if ! grep -h --color=auto "All heap blocks were freed -- no leaks are possible" valgrind.log; then \
			echo "Pamięć nie została zwolniona dla: $$MAP"; \
			exit 1; \
		fi; \
		if grep -h --color=auto "ERROR SUMMARY: [^0]" valgrind.log; then \
			echo "Błędy dla mapy: $$MAP"; \
			exit 1; \
		fi; \
		if [ "${TEST_WAIT}" = "true" ]; then \
			read -n 1 -s; \
		fi; \
	done

	@echo -e "\033[1mUruchamianie testów ogólnych jako stdin:\033[0m"
	@for MAP in ${VALID_MAPS}; do \
		echo -e "\nTestowanie map: $$MAP"; \
		cat $$MAP | valgrind --log-file=valgrind.log ./${NAME}; \
		if ! grep -h --color=auto "All heap blocks were freed -- no leaks are possible" valgrind.log; then \
			echo "Pamięć nie została zwolniona dla: $$MAP"; \
			exit 1; \
		fi; \
		if grep -h --color=auto "ERROR SUMMARY: [^0]" valgrind.log; then \
			echo "Błędy dla mapy: $$MAP"; \
			exit 1; \
		fi; \
		if [ "${TEST_WAIT}" = "true" ]; then \
			read -n 1 -s; \
		fi; \
	done

test: all test_f_option test_stdin
	@echo -e "\033[1;32mTesty przebiegły pomyślnie!!!\033[0m"

clean:
	rm -f ${OBJECTS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
