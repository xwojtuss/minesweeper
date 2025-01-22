#include "minesweeper.h"

FILE	*get_input(int argc, char **argv)
{
	int		option;
	char	*filename;
	FILE	*input;

	filename = NULL;
	input = stdin;
	while ((option = getopt(argc, argv, ":f:")) != -1)
	{
		switch (option)
		{
		case 'f':
			if (filename)
				err_usage("Za dużo plików");
			filename = optarg;
			break ;
		case ':':
			err_usage("Podana flaga wymaga argumentu");
			break ;
		case '?':
			fprintf(stderr, "Błąd\nNieznana opcja: %c\n", optopt);
			exit(EXIT_FAILURE);
			break ;
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

void	get_x_y(FILE *input, char buffer[BUFFER_SIZE], t_game_info *info)
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
	info->rows = atoi(token);
	token = strtok(NULL, " ");
	if (!token || !is_valid(token, '0', '9'))
		err_close("Błędny rozmiar mapy", input);
	info->cols = atoi(token);
	if (info->cols <= 0 || info->rows <= 0)
		err_close("Błędny rozmiar mapy", input);
	token = strtok(NULL, " ");
	if (token)
		err_close("Za dużo parametrów", input);
}

int	get_size(FILE *input, t_game_info *info)
{
	char	buffer[BUFFER_SIZE];
	char	*line;

	printf("Podaj cyfrę poziomu trudności (1-4): ");
	line = fgets(buffer, BUFFER_SIZE, input);
	if (!line)
		err_close_perror("Błąd podczas czytania z pliku", input);
	if (line[0] == '1' && (line[1] == '\n' || line[1] == '\0'))
		return (info->cols = 9, info->rows = 9, info->mines = 10, 1);
	else if (line[0] == '2' && (line[1] == '\n' || line[1] == '\0'))
		return (info->cols = 16, info->rows = 16, info->mines = 40, 2);
	else if (line[0] == '3' && (line[1] == '\n' || line[1] == '\0'))
		return (info->cols = 30, info->rows = 16, info->mines = 99, 3);
	else if (line[0] == '4' && (line[1] == '\n' || line[1] == '\0'))
	{
		get_x_y(input, buffer, info);
		return (info->mines = 0, 1);
	}
	else
		err_close("Zły poziom trudności", input);
	return (0);
}

int	load_map(FILE *input, char **grid, t_game_info *info)
{
	char	*buffer;
	char	*line;

	printf("Podaj mapę (0-puste pole, 1-bomba)\n");
	buffer = (char *)calloc(info->cols + 2, sizeof(char));
	if (!buffer)
		err_close_free("Alokacja pamięci nie powiodła się", input, grid,
			info->cols);
	for (int i = 0; i < info->rows; i++)
	{
		line = fgets(buffer, info->cols + 2, input);
		if (!line || line[0] == '\0' || line[info->cols] != '\n'
			|| !is_valid(line, '0', '1'))
		{
			free(buffer);
			err_close_free("Zły format mapy", input, grid, info->cols);
		}
		else
		{
			for (int j = 0; j < info->cols; j++)
			{
				if (line[j] == '1')
				{
					set_bomb(&grid[j][i]);
					add_count_surround(grid, i, j, info);
				}
			}
		}
	}
	free(buffer);
	return (0);
}
