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
				printf("%s", count_sumbols[(grid[i][j] & COUNT)>>COUNT_START_BIT]);
			else if (!is_flagged(grid[i][j]))
				printf("⬜");
			else
				printf("🚩");
		}
		printf("\n");
	}
}

#include <getopt.h>

FILE	*get_input(int argc, char **argv)
{
	int		option;
	char	*filename;
	FILE	*input;

	filename = NULL;
	input = stdin;
	while((option = getopt(argc, argv, ":f:")) != -1)
	{
		switch(option)
		{
			case 'f':
				if (filename)
					err_usage("Za dużo plików");
				filename = optarg;
				break;
			case ':':
				err_usage("Podana flaga wymaga argumentu");
				break;
			case '?':
				fprintf(stderr, "Błąd\nNieznana opcja: %c\n", optopt);
				exit(EXIT_FAILURE);
				break;
		}
	}
	if (filename)
		return (fopen(filename, "r"));
	if (argc > 1)
		err_usage("Za dużo argumentów wywołania");
	return (input);
}

bool	is_valid(char *token, char from, char to)
{
	for (int i = 0; token[i]; i++)
	{
		if (token[i] == '\n' && token[i + 1] == '\0')
			return (true);
		if (token[i] < from || token[i] > to)
			return (false);
	}
	return (true);
}

void	get_x_y(FILE *input, int *x, int *y, char buffer[BUFFER_SIZE])
{
	char	*line;
	char	*token;

	printf("Podaj rozmiar własnej mapy (wiersze kolumny): ");
	line = fgets(buffer, BUFFER_SIZE, input);
	if (!line)
		err_close_perror("Nie udało się przeczytać linijki", input);
	token = strtok(line, " ");
	if (!token || !is_valid(token, '0', '9'))
		err_close("Błędny rozmiar mapy", input);
	*x = atoi(token);
	token = strtok(NULL, " ");
	if (!token || !is_valid(token, '0', '9'))
		err_close("Błędny rozmiar mapy", input);
	*y = atoi(token);
	if (*x <= 0 || *y <= 0)
		err_close("Błędny rozmiar mapy", input);
	token = strtok(NULL, " ");
	if (token)
		err_close("Za dużo parametrów", input);
}

int	get_size(FILE *input, int *x, int *y, int *mines)
{
	char	buffer[BUFFER_SIZE];
	char	*line;

	printf("Podaj cyfrę poziomu trudności (1-4): ");
	line = fgets(buffer, BUFFER_SIZE, input);
	if (!line)
		err_close_perror("Błąd podczas czytania z pliku", input);
	if (line[0] == '1' && (line[1] == '\n' || line[1] == '\0'))
		return (*x = 9, *y = 9, *mines = 10, 1);
	else if (line[0] == '2' && (line[1] == '\n' || line[1] == '\0'))
		return (*x = 16, *y = 16, *mines = 40, 2);
	else if (line[0] == '3' && (line[1] == '\n' || line[1] == '\0'))
		return (*x = 16, *y = 30, *mines = 99, 3);
	else if (line[0] == '4' && (line[1] == '\n' || line[1] == '\0'))
	{
		get_x_y(input, x, y, buffer);
		return (*mines = 0, 1);
	}
	else
	{
		err_close("Zły poziom trudności", input);
	}
	return (0);
}

void	print_diff_levels(void)
{
	printf(COLOR_BOLD "Poziomy trudności:\n");
	printf("1." COLOR_OFF "\tŁatwy - 9x9, 10min\n");
	printf(COLOR_BOLD "2." COLOR_OFF "\tŚredni - 16x16, 40min\n");
	printf(COLOR_BOLD "3." COLOR_OFF "\tTrudny - 16x30, 99min\n");
	printf(COLOR_BOLD "4." COLOR_OFF "\tWłasna plansza\n");
}


int	load_map(FILE *input, int x, int y, short **grid)
{
	char	*buffer;
	char	*line;

	buffer = (char *)calloc(y + 2, sizeof(char));
	if (!buffer)
		err_close_free("Alokacja pamięci nie powiodła się", input, grid, x);
	for (int i = 0; i < x; i++)
	{
		line = fgets(buffer, y + 2, input);
		if (line[y] != '\n' || !is_valid(line, '0', '1'))
		{
			free(buffer);
			err_close_free("Zły format mapy", input, grid, x);
		}
		else
		{
			for (int j = 0; j < y; j++)
				if (line[j] == '1')
					set_bomb(&grid[i][j]);
		}
	}
	free(buffer);
	return (0);
}

bool	bomb_check(short **grid, int r, int c, int rows, int cols)
{
	if(c>0)
	{
		if((grid[c-1][r] & COUNT)>>COUNT_START_BIT>3)
		{
			return 1;
		}
		if(r>0)
		{
			if((grid[c-1][r-1] & COUNT)>>COUNT_START_BIT>3)
			{
				return 1;
			}
		}
		if(r<rows-1)
		{
			if((grid[c-1][r+1] & COUNT)>>COUNT_START_BIT>3)
			{
				return 1;
			}
		}
	}
	if(r>0)
	{
		if((grid[c][r-1] & COUNT)>>COUNT_START_BIT>3)
			{
				return 1;
			}
	}
	if(r<rows-1)
	{
		if((grid[c][r+1] & COUNT)>>COUNT_START_BIT>3)
			{
				return 1;
			}
	}
	if(c<cols-1)
	{
		if(r>0)
		{
			if((grid[c+1][r-1] & COUNT)>>COUNT_START_BIT>3)
				{
					return 1;
				}
		}
		if(r<rows-1)
		{
			if((grid[c+1][r+1] & COUNT)>>COUNT_START_BIT>3)
				{
					return 1;
				}
		}
		if((grid[c+1][r] & COUNT)>>COUNT_START_BIT>3)
			{
				return 1;
			}
	}

return 0;
}

void	place_bomb(short **grid, int rows, int cols, int mines)
{

	srand(time(NULL));
	int mine_c = 0;
	int rand_r, rand_c;
	printf("in\n");
	while (mine_c!=mines)
	{
		rand_r=rand()%rows;
		rand_c=rand()%cols;
		if (!is_bomb(grid[rand_c][rand_r]))
		{
			if(bomb_check(grid, rand_r, rand_c, rows, cols)==0)
			{
				set_bomb(&grid[rand_c][rand_r]);
				mine_c++;
				if(rand_c>0)
				{
					add_count(&grid[rand_c-1][rand_r]);
					if(rand_r>0)
					{
					add_count(&grid[rand_c-1][rand_r-1]);
					}
					if(rand_r<rows-1)
					{
					add_count(&grid[rand_c-1][rand_r+1]);
					}
				}
				if(rand_r>0)
				{
				add_count(&grid[rand_c][rand_r-1]);
				}
				if(rand_r<rows-1)
				{
				add_count(&grid[rand_c][rand_r+1]);
				}
				if(rand_c<cols-1)
				{
					if(rand_r>0)
					{
					add_count(&grid[rand_c+1][rand_r-1]);
					}
					if(rand_r<rows-1)
					{
					add_count(&grid[rand_c+1][rand_r+1]);
					}
					add_count(&grid[rand_c+1][rand_r]);
				}
			}
		}
	}
}


void reveal_ogrid(short **grid, int r, int c, int rows, int cols)
{
	if(is_flagged(grid[c][r]))
	{
		return;
	}
	else if(is_revealed(grid[c][r]))
	{
		return;
	}
	else
	{
		reveal(&grid[c][r]);
		if((grid[c][r] & COUNT)>>COUNT_START_BIT==0)
		{
			if(c>0)
			{
				reveal_ogrid(grid, r, c-1, rows, cols);
				if(r>0)
				{
					reveal_ogrid(grid, r-1, c-1, rows, cols);
				}
				if(r<rows-1)
				{
					reveal_ogrid(grid, r+1, c-1, rows, cols);
				}
			}
			if(r>0)
			{
				reveal_ogrid(grid, r-1, c, rows, cols);
			}
			if(r<rows-1)
			{
				reveal_ogrid(grid, r+1, c, rows, cols);
			}
			if(c<cols-1)
			{
				reveal_ogrid(grid, r, c+1, rows, cols);
				if(r>0)
				{
					reveal_ogrid(grid, r-1, c+1, rows, cols);
				}
				if(r<rows-1)
				{
					reveal_ogrid(grid, r+1, c+1, rows, cols);
				}
			}
		}
	}


}



void reveal_grid(short **grid, int r, int c, int rows, int cols)
{
	if(r<0 || r>=rows)
	{
		printf("niepoprawna wartosc kolumny: %d\n",r);
		return;
	}
	else if(c<0 || c>=cols)
	{
		printf("niepoprawna wartosc wiersza: %d\n",c);
		return;
	}
	else if(is_flagged(grid[c][r]))
	{
		printf("pole posiada flage!\n");
		return;
	}
	else if(is_bomb(grid[c][r]))
	{
		// add failure
		return;
	}
	else if(is_revealed(grid[c][r]))
	{
		printf("pole jest juz odkryte!\n");
		return;
	}
	else
	{
		reveal(&grid[c][r]);
		if((grid[c][r] & COUNT)>>COUNT_START_BIT==0)
		{
			if(c>0)
			{
				reveal_ogrid(grid, r, c-1, rows, cols);
				if(r>0)
				{
					reveal_ogrid(grid, r-1, c-1, rows, cols);
				}
				if(r<rows-1)
				{
					reveal_ogrid(grid, r+1, c-1, rows, cols);
				}
			}
			if(r>0)
			{
				reveal_ogrid(grid, r-1, c, rows, cols);
			}
			if(r<rows-1)
			{
				reveal_ogrid(grid, r+1, c, rows, cols);
			}
			if(c<cols-1)
			{
				reveal_ogrid(grid, r, c+1, rows, cols);
				if(r>0)
				{
					reveal_ogrid(grid, r-1, c+1, rows, cols);
				}
				if(r<rows-1)
				{
					reveal_ogrid(grid, r+1, c+1, rows, cols);
				}
			}
		}
	}


}

void	start_game(FILE *input, short **grid, int rows, int cols)
{
	char	line[42];
	char	command;
	int		x;
	int		y;

	while (true)
	{
		bzero(line, 42);
		print_field(grid, rows, cols, false);
		printf("> ");
		fgets(line, 42, input);
		if (!strchr(line, '\n') || sscanf(line, "%c %i %i", &command, &x, &y) < 3 || (command != 'r' && command != 'f'))
		{
			printf("Zła komenda, proszę podać następną\n");
			// continue ;
			break ; //temporary
		}
		if (x >= rows || x < 0 || y >= cols || y < 0)
		{
			printf("x lub/i y poza granicami mapy\n");
			continue ;
		}
		if (command == 'f')
			change_flag(&grid[x][y]);
		else if (command == 'r' && !is_flagged(grid[x][y]))
			reveal(&grid[x][y]);
		// if all bombs flagged or bomb revealed
			// break
	}
}

int	main(int argc, char **argv)
{	
	short	**grid;
	int		cols;
	int		rows;
	int		difficulty;
	int		mines;
	FILE	*input;
	
	input = get_input(argc, argv);
	if (!input)
		err_close_perror("Nie udało się otworzyć pliku", input);
	(void)grid;
	cols = 0;
	rows = 0;
	print_diff_levels();
	difficulty = get_size(input, &cols, &rows, &mines);
	printf("%d\n", difficulty);
	grid = create_array(rows, cols);
	if (!grid)
		err_close("Alokacja pamięci nie powiodła się", input);
	if (mines == 0)
	{

	}
		// mines = load_map(input, cols, rows, grid); //buffer for fgets will be cols * 2
	// else
		// generate_map();	
	place_bomb(grid, rows, cols, mines);
	print_field(grid, rows, cols, false);
	change_flag(&grid[0][0]);
	start_game(input, grid, rows, cols);
	reveal_grid(grid,1,1,rows,cols);
	reveal_grid(grid,7,7,rows,cols);
	print_field(grid,rows,cols,false);
	reveal_grid(grid,0,9,rows,cols);
	print_field(grid,rows,cols,false);
	printf("after finished:\n");
	print_field(grid, rows, cols, true);
	free_grid(grid, cols);
	if (input != stdin)
		fclose(input);
}
