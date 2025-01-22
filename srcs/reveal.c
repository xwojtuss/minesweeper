#include "minesweeper.h"

static void	reveal_ogrid(char **grid, int r, int c, t_game_info *info,
		int *revealed)
{
	if (is_flagged(grid[c][r]) || is_revealed(grid[c][r]))
		return ;
	reveal(&grid[c][r]);
	(*revealed)++;
	if ((grid[c][r] & COUNT) >> COUNT_START_BIT != 0)
		return ;
	if (c > 0)
	{
		reveal_ogrid(grid, r, c - 1, info, revealed);
		if (r > 0)
			reveal_ogrid(grid, r - 1, c - 1, info, revealed);
		if (r < info->rows - 1)
			reveal_ogrid(grid, r + 1, c - 1, info, revealed);
	}
	if (r > 0)
		reveal_ogrid(grid, r - 1, c, info, revealed);
	if (r < info->rows - 1)
		reveal_ogrid(grid, r + 1, c, info, revealed);
	if (c < info->cols - 1)
	{
		reveal_ogrid(grid, r, c + 1, info, revealed);
		if (r > 0)
			reveal_ogrid(grid, r - 1, c + 1, info, revealed);
		if (r < info->rows - 1)
			reveal_ogrid(grid, r + 1, c + 1, info, revealed);
	}
}

int	reveal_grid(char **grid, int r, int c, t_game_info *info)
{
	int	revealed;

	revealed = 0;
	if (is_flagged(grid[c][r]) || is_revealed(grid[c][r]))
		return (revealed);
	reveal(&grid[c][r]);
	revealed++;
	if ((grid[c][r] & COUNT) >> COUNT_START_BIT != 0)
		return (revealed);
	if (c > 0)
	{
		reveal_ogrid(grid, r, c - 1, info, &revealed);
		if (r > 0)
			reveal_ogrid(grid, r - 1, c - 1, info, &revealed);
		if (r < info->rows - 1)
			reveal_ogrid(grid, r + 1, c - 1, info, &revealed);
	}
	if (r > 0)
		reveal_ogrid(grid, r - 1, c, info, &revealed);
	if (r < info->rows - 1)
		reveal_ogrid(grid, r + 1, c, info, &revealed);
	if (c < info->cols - 1)
	{
		reveal_ogrid(grid, r, c + 1, info, &revealed);
		if (r > 0)
			reveal_ogrid(grid, r - 1, c + 1, info, &revealed);
		if (r < info->rows - 1)
			reveal_ogrid(grid, r + 1, c + 1, info, &revealed);
	}
	return (revealed);
}
