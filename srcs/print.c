#include "minesweeper.h"

void	print_score(t_game_info *info)
{
	printf(COLOR_BOLD "Liczba punktów:\t%i\n" COLOR_OFF, info->points);
}

void	print_field(char **grid, int rows, int cols, bool is_finished)
{
	char *count_sumbols[9] = {"0️⃣ ", "1️⃣ ", "2️⃣ ", "3️⃣ ", "4️⃣ ", "5️⃣ ", "6️⃣ ", "7️⃣ ", "8️⃣ "};

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (is_finished && is_bomb(grid[j][i]) && is_flagged(grid[j][i]))
				printf("💣");
			else if (is_finished && is_bomb(grid[j][i]))
				printf("💥");
			else if ((is_revealed(grid[j][i]) || is_finished) && !is_flagged(grid[j][i]))
				printf("%s", count_sumbols[(grid[j][i] & COUNT)>>COUNT_START_BIT]);
			else if (!is_flagged(grid[j][i]))
				printf("⬜");
			else
				printf("🚩");
		}
		printf("\n");
	}
}

void	print_end_game(char **grid, t_game_info *info, bool is_success)
{
	printf("\n");
	system("clear");
	print_field(grid, info->rows, info->cols, true);
	printf("Gra zakończona ");
	if (is_success)
		printf("sukcesem (1)");
	else
		printf("niepowodzeniem (0)");
	printf("\nIlość poprawnych kroków:\t%i\n", info->instructions);
	printf("Ilość zdobytych punktów:\t%i\n", info->points);
}

void	print_diff_levels(void)
{
	printf(COLOR_BOLD "Poziomy trudności:\n");
	printf("1." COLOR_OFF "\tŁatwy - 9x9, 10min\n");
	printf(COLOR_BOLD "2." COLOR_OFF "\tŚredni - 16x16, 40min\n");
	printf(COLOR_BOLD "3." COLOR_OFF "\tTrudny - 16x30, 99min\n");
	printf(COLOR_BOLD "4." COLOR_OFF "\tWłasna plansza\n");
}
