

#include <stdlib.h>
#include <stdio.h>

short	**create_array(unsigned int rows, unsigned int cols)
{
	short	**result;

	result = (short **)calloc(sizeof(short *), cols);
	if (!result)
		exit(EXIT_FAILURE);
	for (int i = 0; i < cols; i++)
	{
		result[i] = (short *)calloc(sizeof(short), rows);
		if (!result[i])
		{
			for (int j = 0; j < i; j++)
				free(result[i]);
			free(result);
			exit(EXIT_FAILURE);
		}
	}
	return (result);
}

int main(void)
{
	short	**grid;
	int		cols;
	int		rows;

	grid = create_array(rows, cols);
	//generate tiles
	//start game
}
