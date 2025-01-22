#include "minesweeper.h"

int	main(int argc, char **argv)
{
	char		**grid;
	FILE		*input;
	t_game_info	info;

	init_info(&info);
	srand(time(NULL));
	input = get_input(argc, argv);
	if (!input)
		err_close_perror("Nie udało się otworzyć pliku", input);
	print_diff_levels();
	info.difficulty = get_size(input, &info);
	grid = create_array(info.cols, info.rows);
	if (!grid)
		err_close("Alokacja pamięci nie powiodła się", input);
	if (info.mines == 0)
		info.mines = load_map(input, grid, &info);
	else
		first_move(input, grid, &info);
	if (start_game(input, grid, &info))
	{
		print_end_game(grid, &info, true);
		get_leaderboard(&info, input);
	}
	else
		print_end_game(grid, &info, false);
	free_grid(grid, info.cols);
	if (input != stdin)
		fclose(input);
}
