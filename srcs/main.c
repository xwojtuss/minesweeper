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

#include "get_next_line.h"
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
					err_usage("Too many files");
				printf("Given File: %s\n", optarg);
				filename = optarg;
				break;
			case ':':
				printf("option needs a value\n");
				break;
			case '?':
				printf("unknown option: %c\n", optopt);
				break;
		}
	}
	if (filename)
		input = fopen(filename, "r");
	return (input);
}

int	main(int argc, char **argv)
{
	short	**grid;
	int		cols;
	int		rows;
	FILE	*input;
	
	input = get_input(argc, argv);
	if (!input)
		err("Could not open file");
	if (input != stdin)
		fclose(input);
	(void)grid;
	cols = 9;
	rows = 9;
	grid = create_array(rows, cols);
	set_bomb(&grid[0][0]);
	set_bomb(&grid[0][1]);
	print_field(grid, rows, cols, false);
	change_flag(&grid[0][0]);
	// generate tiles
	// start game
	print_field(grid, rows, cols, false);
	printf("after finished:\n");
	print_field(grid, rows, cols, true);
	free_grid(grid, cols);
}
