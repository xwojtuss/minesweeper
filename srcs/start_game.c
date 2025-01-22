#include "minesweeper.h"

static bool	is_all_revealed(char **grid, int rows, int cols)
{
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
			if ((is_bomb(grid[i][j]) && !is_flagged(grid[i][j]))
				|| (!is_bomb(grid[i][j]) && !is_revealed(grid[i][j]))
				|| (!is_bomb(grid[i][j]) && is_flagged(grid[i][j])))
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
		if (sscanf(line, "%c %i %i", &command, &r, &c) < 3 || (command != 'r'
				&& command != 'f'))
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
		else if (command == 'r' && !is_flagged(grid[c][r]) && !is_revealed(grid[c][r]))
			info->points += reveal_grid(grid, r, c, info) * info->difficulty;
		else
			continue ;
		info->instructions++;
	}
	printf("\n");
	system("clear");
	if (is_all_revealed(grid, info->rows, info->cols))
		return (true);
	return (false);
}

void	first_move(FILE *input, char **grid, t_game_info *info)
{
	char line[42];
	char command;
	int r;
	int c;
	system("clear");
	while (info->points == 0)
	{
		bzero(line, 42);
		print_score(info);
		print_field(grid, info->rows, info->cols, false);
		printf("> ");
		fgets(line, 42, input);
		system("clear");
		if (line[0] == '\0')
			break ;
		if (sscanf(line, "%c %i %i", &command, &r, &c) < 3 || command != 'r')
		{
			printf("Zła komenda, proszę podać następną\n");
			continue ;
		}
		if (r >= info->rows || r < 0 || c >= info->cols || c < 0)
		{
			printf("x lub/i y poza granicami mapy\n");
			continue ;
		}
		place_bombs(grid, info, r, c);
		info->points += reveal_grid(grid, r, c, info) * info->difficulty;
		info->instructions++;
	}
}