#include "minesweeper.h"

short	**create_array(unsigned int rows, unsigned int cols)
{
	short	**result;

	result = (short **)calloc(sizeof(short *), cols);
	if (!result)
		err("Memory allocation failure");
	for (unsigned int i = 0; i < cols; i++)
	{
		result[i] = (short *)calloc(sizeof(short), rows);
		if (!result[i])
		{
			for (unsigned int j = 0; j < i; j++)
				free(result[i]);
			free(result);
			err("Memory allocation failure");
		}
	}
	return (result);
}

void	free_grid(short **grid, int cols)
{
	for (int i = 0; i < cols; i++)
		free(grid[i]);
	free(grid);
}
