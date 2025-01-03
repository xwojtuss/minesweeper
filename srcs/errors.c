#include "minesweeper.h"

void	err_usage(char *message)
{
	fprintf(stderr, "Błąd\n%s\n", message);
	print_usage();
	exit(EXIT_FAILURE);
}

void	err(char *message)
{
	fprintf(stderr, "Błąd\n%s\n", message);
	exit(EXIT_FAILURE);
}

void	err_close(char *message, FILE *to_close)
{
	fprintf(stderr, "Błąd\n%s\n", message);
	if (to_close != stdin && to_close != NULL)
		fclose(to_close);
	exit(EXIT_FAILURE);
}

void	err_close_perror(char *message, FILE *to_close)
{
	fprintf(stderr, "Błąd\n");
	if (errno != 0)
		perror(message);
	else
		fprintf(stderr, "%s\n", message);
	if (to_close != stdin && to_close != NULL)
		fclose(to_close);
	exit(EXIT_FAILURE);
}

void	print_usage(void)
{
	printf("tutaj trzeba opisac\n"); // DOKONCZYC!!!!!!!!!!
	exit(EXIT_FAILURE);
}
