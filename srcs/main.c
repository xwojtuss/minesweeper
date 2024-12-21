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

int	main(int argc, char **argv)
{
	short	**grid;
	char	*line;
	int		fd;
	int		cols;
	int		rows;

	if (argc > 1)
		print_usage();
	else if (argc == 1)
		fd = STDIN_FILENO;
	else
		fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		err("Could not open file");
	(void)grid;
	cols = 9;
	rows = 9;
	grid = create_array(rows, cols);
	line = get_next_line(fd);
	if (line && line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
	printf("%s\n", line);
	free(line);
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
