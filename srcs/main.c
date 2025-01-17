/*

Komórka to char, gdzie najmniej znaczący bit oznacza:
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

bool	is_all_revealed(char **grid, int rows, int cols)
{
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
			if ((is_bomb(grid[i][j]) && !is_flagged(grid[i][j])) || (!is_bomb(grid[i][j]) && !is_revealed(grid[i][j])) || (!is_bomb(grid[i][j]) && is_flagged(grid[i][j])))
				return (false);
	return (true);
}

bool	start_game(FILE *input, char **grid, t_game_info *info)
{
	char	line[42];
	char	command;
	int		r;
	int		c;

	system("clear");
	while (true)
	{
		if (is_all_revealed(grid, info->rows, info->cols))
			return (true);
		bzero(line, 42);
		print_score(info);
		print_field(grid, info->rows, info->cols, false);
		printf("> ");
		fgets(line, 42, input);
		system("clear");
		if (line[0] == '\0')
			break ;
		if (!strchr(line, '\n') || sscanf(line, "%c %i %i", &command, &r, &c) < 3 || (command != 'r' && command != 'f'))
		{
			printf("Zła komenda, proszę podać następną\n");
			continue ;
		}
		if (r >= info->rows || r < 0 || c >= info->cols || c < 0)
		{
			printf("x lub/i y poza granicami mapy\n");
			continue ;
		}
		if (command == 'f' && !is_revealed(grid[c][r]))
			change_flag(&grid[c][r]);
		else if (command == 'r' && is_bomb(grid[c][r]))
			return (false);
		else if (command == 'r' && !is_flagged(grid[c][r]))
			info->points += reveal_grid(grid, r, c, info) * info->difficulty;
		info->instructions++;
	}
	printf("\n");
	system("clear");
	if (is_all_revealed(grid, info->rows, info->cols))
		return (true);
	return (false);
}

void	init_info(t_game_info *info)
{
	info->cols = 0;
	info->difficulty = 0;
	info->instructions = 0;
	info->mines = 0;
	info->points = 0;
	info->rows = 0;
}

void first_move(FILE *input, char **grid, t_game_info *info)
{
	char	line[42];
	char	command;
	int		r;
	int		c;
	system("clear");
	while(info->points == 0)
	{
		bzero(line, 42);
		print_score(info);
		print_field(grid, info->rows, info->cols, false);
		printf("> ");
		fgets(line, 42, input);
		system("clear");
		if (line[0] == '\0')
			break ;
		if (sscanf(line, "%c %i %i", &command, &r, &c) < 3 || command!= 'r')
		{
			printf("Zła komenda, proszę podać następną\n");
			continue ;
		}
		if (r >= info->rows || r < 0 || c >= info->cols || c < 0)
		{
			printf("x lub/i y poza granicami mapy\n");
			continue ;
		}
		place_bomb(grid, info, r, c);
		info->points += reveal_grid(grid, r, c, info) * info->difficulty;
	}
}
int	main(int argc, char **argv)
{	
	char	**grid;
	FILE	*input;
	t_game_info	info;
	
	init_info(&info);
	srand(time(NULL));
	input = get_input(argc, argv);
	if (!input)
		err_close_perror("Nie udało się otworzyć pliku", input);
	print_diff_levels();
	info.difficulty = get_size(input, &info);
	grid = create_array(info.cols, info.rows);
	if (!grid)
		err_close("Alokacja pamięci nie powiodła się", input);
	if (info.mines == 0)
		info.mines = load_map(input, grid, &info);
	else
	{
		first_move(input, grid, &info);	
	}
	if (start_game(input, grid, &info))
	{
		print_end_game(grid, &info, true);
		get_leaderboard(&info, input);
	}
	else
		print_end_game(grid, &info, false);
	free_grid(grid, info.cols);
	if (input != stdin)
		fclose(input);
}
