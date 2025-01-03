/*

Komórka to short, gdzie najmniej znaczący bit oznacza:
	1 - bomba
	0 - pusto
Drugi najmniej znaczący bit oznacza:
	1 - jest flaga
	0 - nie ma flagi
Trzeci najmniej znaczący bit oznacza:
	1 - jest odkryta
	0 - nie jest odkryta
Czwarty, piąty, szósty bit to informacja o tym ile jest bomb dookoła

*/

#include "minesweeper.h"

void	print_field(short **grid, int rows, int cols, bool is_finished)
{
	char *count_sumbols[9] = {"0️⃣ ", "1️⃣ ", "2️⃣ ", "3️⃣ ", "4️⃣ ", "5️⃣ ", "6️⃣ ", "7️⃣ ", "8️⃣ "};

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (is_finished && is_bomb(grid[i][j]) && is_flagged(grid[i][j]))
				printf("💣");
			else if (is_finished && is_bomb(grid[i][j]))
				printf("💥");
			else if ((is_revealed(grid[i][j]) || is_finished) && !is_flagged(grid[i][j]))
				printf("%s", count_sumbols[grid[i][j] & COUNT]);
			else if (!is_flagged(grid[i][j]))
				printf("⬜");
			else
				printf("🚩");
		}
		printf("\n");
	}
}

#include <getopt.h>

FILE	*get_input(int argc, char **argv)
{
	int		option;
	char	*filename;
	FILE	*input;

	filename = NULL;
	input = stdin;
	while((option = getopt(argc, argv, ":f:")) != -1)
	{
		switch(option)
		{
			case 'f':
				if (filename)
					err_usage("Za dużo plików");
				filename = optarg;
				break;
			case ':':
				err_usage("Podana flaga wymaga argumentu");
				break;
			case '?':
				fprintf(stderr, "Błąd\nNieznana opcja: %c\n", optopt);
				exit(EXIT_FAILURE);
				break;
		}
	}
	if (filename)
		return (fopen(filename, "r"));
	if (argc > 1)
		err_usage("Za dużo argumentów wywołania");
	return (input);
}

bool	is_valid(char *token)
{
	for (int i = 0; token[i]; i++)
	{
		if (token[i] == '\n' && token[i + 1] == '\0')
			return (true);
		if (token[i] < '0' || token[i] > '9')
			return (false);
	}
	return (true);
}

void	get_x_y(FILE *input, int *x, int *y, char buffer[BUFFER_SIZE])
{
	char	*line;
	char	*token;

	printf("Podaj rozmiar własnej mapy: ");
	line = fgets(buffer, BUFFER_SIZE, input);
	if (!line)
		err_close_perror("Nie udało się przeczytać linijki", input);
	token = strtok(line, " ");
	if (!token || !is_valid(token))
		err_close("Błędny rozmiar mapy", input);
	*x = atoi(token);
	token = strtok(NULL, " ");
	if (!token || !is_valid(token))
		err_close("Błędny rozmiar mapy", input);
	*y = atoi(token);
	if (*x <= 0 || *y <= 0)
		err_close("Błędny rozmiar mapy", input);
	token = strtok(NULL, " ");
	if (token)
		err_close("Za dużo parametrów", input);
}

void	get_size(FILE *input, int *x, int *y, int *mines)
{
	char	buffer[BUFFER_SIZE];
	char	*line;

	printf("Podaj cyfrę poziomu trudności (1-4): ");
	line = fgets(buffer, BUFFER_SIZE, input);
	if (!line)
		err_close_perror("Błąd podczas czytania z pliku", input);
	if (line[0] == '1' && (line[1] == '\n' || line[1] == '\0'))
		*x = 9, *y = 9, *mines = 10;
	else if (line[0] == '2' && (line[1] == '\n' || line[1] == '\0'))
		*x = 16, *y = 16, *mines = 40;
	else if (line[0] == '3' && (line[1] == '\n' || line[1] == '\0'))
		*x = 16, *y = 30, *mines = 99;
	else if (line[0] == '4' && (line[1] == '\n' || line[1] == '\0'))
	{
		get_x_y(input, x, y, buffer);
		*mines = 0;
	}
	else
		err_close("Zły poziom trudności", input);
}

void	print_diff_levels(void)
{
	printf(COLOR_BOLD "Poziomy trudności:\n");
	printf("1." COLOR_OFF "\tŁatwy - 9x9, 10min\n");
	printf(COLOR_BOLD "2." COLOR_OFF "\tŚredni - 16x16, 40min\n");
	printf(COLOR_BOLD "3." COLOR_OFF "\tTrudny - 16x30, 99min\n");
	printf(COLOR_BOLD "4." COLOR_OFF "\tWłasna plansza\n");
}

int	main(int argc, char **argv)
{
	short	**grid;
	int		cols;
	int		rows;
	int		mines;
	FILE	*input;
	
	input = get_input(argc, argv);
	if (!input)
		err_close_perror("Nie udało się otworzyć pliku", input);
	(void)grid;
	cols = 0;
	rows = 0;
	print_diff_levels();
	get_size(input, &cols, &rows, &mines);
	grid = create_array(rows, cols);
	if (!grid)
		err_close("Alokacja pamięci nie powiodła się", input);
	if (mines == 0)
		// mines = load_map(input, cols, rows, grid); //buffer for fgets will be cols * 2
	// else
		// generate_map();
	set_bomb(&grid[0][0]);
	set_bomb(&grid[0][1]);
	print_field(grid, rows, cols, false);
	change_flag(&grid[0][0]);
	// start game
	print_field(grid, rows, cols, false);
	printf("after finished:\n");
	print_field(grid, rows, cols, true);
	free_grid(grid, cols);
	if (input != stdin)
		fclose(input);
}
