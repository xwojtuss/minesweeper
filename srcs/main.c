

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	short	**grid;

	grid = (short **)calloc(sizeof(short *), cols);
	if (!grid)
		//handle memory failure
	for (int i = 0; i < rows; i++)
		grid[i] = (short *)calloc(sizeof(short), rows);
		if (!grid[i])
			//handle memory failure
	//create array
	//generate tiles
	//start game
}
