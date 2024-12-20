

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*

Komórka to short, gdzie najmniej znaczący bit oznacza:
	1 - bomba
	0 - pusto
Drugi najmniej znaczący bit oznacza:
	1 - jest flaga
	0 - nie ma flagi
Trzeci, czwarty, piąty bit to informacja o tym ile jest bomb dookoła

*/

char	*get_next_line(int fd);

short	**create_array(unsigned int rows, unsigned int cols)
{
	short	**result;

	result = (short **)calloc(sizeof(short *), cols);
	if (!result)
		exit(EXIT_FAILURE);
	for (unsigned int i = 0; i < cols; i++)
	{
		result[i] = (short *)calloc(sizeof(short), rows);
		if (!result[i])
		{
			for (int j = 0; j < i; j++)
				free(result[i]);
			free(result);
			exit(EXIT_FAILURE);
		}
		result[i] = 0;
	}
	return (result);
}

int main(void)
{
	short	**grid;
	char	*line;
	int		cols;
	int		rows;

	(void)grid;
	cols = 9;
	rows = 9;
	grid = create_array(rows, cols);
	line = get_next_line(STDIN_FILENO);
	printf("%s\n", line);
	//generate tiles

	//start game

	free_grid(grid);
}
