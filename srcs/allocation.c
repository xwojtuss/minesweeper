#include "minesweeper.h"

void	init_info(t_game_info *info)
{
	info->cols = 0;
	info->difficulty = 0;
	info->instructions = 0;
	info->mines = 0;
	info->points = 0;
	info->rows = 0;
}

char	**create_array(unsigned int cols, unsigned int rows)
{
	char	**result;

	result = (char **)calloc(sizeof(char *), cols);
	if (!result)
		return (NULL);
	for (unsigned int i = 0; i < cols; i++)
	{
		result[i] = (char *)calloc(sizeof(char), rows);
		if (!result[i])
		{
			for (unsigned int j = 0; j < i; j++)
				free(result[i]);
			free(result);
			return (NULL);
		}
	}
	return (result);
}

void	free_grid(char **grid, int cols)
{
	for (int i = 0; i < cols; i++)
		free(grid[i]);
	free(grid);
}
