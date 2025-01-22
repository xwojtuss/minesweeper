#include "minesweeper.h"

bool	bomb_check(char **grid, int r, int c, t_game_info *info)
{
	if (c > 0)
	{
		if ((grid[c - 1][r] & COUNT) >> COUNT_START_BIT > 3)
			return (1);
		if (r > 0 && (grid[c - 1][r - 1] & COUNT) >> COUNT_START_BIT > 3)
			return (1);
		if (r < info->rows - 1 && (grid[c - 1][r
				+ 1] & COUNT) >> COUNT_START_BIT > 3)
			return (1);
	}
	if (r > 0 && (grid[c][r - 1] & COUNT) >> COUNT_START_BIT > 3)
		return (1);
	if (r < info->rows - 1 && (grid[c][r + 1] & COUNT) >> COUNT_START_BIT > 3)
		return (1);
	if (c < info->cols - 1)
	{
		if (r > 0 && (grid[c + 1][r - 1] & COUNT) >> COUNT_START_BIT > 3)
			return (1);
		if (r < info->rows - 1 && (grid[c + 1][r
				+ 1] & COUNT) >> COUNT_START_BIT > 3)
			return (1);
		if ((grid[c + 1][r] & COUNT) >> COUNT_START_BIT > 3)
			return (1);
	}
	return (0);
}

void	add_count_surround(char **grid, int r, int c, t_game_info *info)
{
	if (c > 0)
	{
		add_count(&grid[c - 1][r]);
		if (r > 0)
			add_count(&grid[c - 1][r - 1]);
		if (r < info->rows - 1)
			add_count(&grid[c - 1][r + 1]);
	}
	if (r > 0)
		add_count(&grid[c][r - 1]);
	if (r < info->rows - 1)
		add_count(&grid[c][r + 1]);
	if (c < info->cols - 1)
	{
		if (r > 0)
			add_count(&grid[c + 1][r - 1]);
		if (r < info->rows - 1)
			add_count(&grid[c + 1][r + 1]);
		add_count(&grid[c + 1][r]);
	}
}

void	place_bomb(char **grid, t_game_info *info, int r, int c)
{
	int	mine_c;

	mine_c = 0;
	int rand_r, rand_c;
	while (mine_c != info->mines)
	{
		rand_r = rand() % info->rows;
		rand_c = rand() % info->cols;
		if (is_bomb(grid[rand_c][rand_r]) || bomb_check(grid, rand_r, rand_c,
				info) != 0 || rand_r == r || rand_c == c)
			continue ;
		set_bomb(&grid[rand_c][rand_r]);
		mine_c++;
		add_count_surround(grid, rand_r, rand_c, info);
	}
}
