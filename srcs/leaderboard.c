#include "minesweeper.h"

static int	compare_scores(const void *a, const void *b)
{
	return (((t_player *)b)->points - ((t_player *)a)->points);
}

static bool	get_name(t_player *new, int *player_count, FILE *input,
		int new_points)
{
	printf("Podaj imię: ");
	if (!fgets(new->name, MAX_NAME_LEN, input))
		return (printf("Puste imię! Nie zapisano do wyników"), false);
	new->name[MAX_NAME_LEN - 1] = '\0';
	new->name[strcspn(new->name, "\n")] = '\0';
	new->points = new_points;
	if (new->name[0] == '\0')
		return (printf("Puste imię! Nie zapisano do wyników"), false);
	player_count++;
	return (true);
}

static void	display_scores(t_player *players, int player_count)
{
	qsort(players, player_count, sizeof(t_player), compare_scores);
	printf(COLOR_BOLD "\nWyniki:\n" COLOR_OFF);
	for (int i = 0; i < player_count && i < 5; i++)
		printf("%d. %s\t%d\n", i + 1, players[i].name, players[i].points);
}

static void	add_player(t_player *players, int player_count)
{
	FILE	*output;

	output = fopen(LEADERBOARD_FILE, "w");
	if (!output)
		return (perror("Nie udało się otworzyć pliku z wynikami"));
	for (int i = 0; i < player_count; i++)
		fprintf(output, "%s\t%d\n", players[i].name, players[i].points);
	fclose(output);
}

void	get_leaderboard(t_game_info *info, FILE *input)
{
	t_player	players[MAX_PLAYERS];
	int			player_count;
	bool		to_add;
	FILE		*file;

	to_add = false;
	player_count = 0;
	file = fopen(LEADERBOARD_FILE, "a+");
	if (!file)
	{
		perror("Nie udało się otworzyć pliku z wynikami");
		return ;
	}
	rewind(file);
	while (fscanf(file, "%127s\t%d", players[player_count].name,
			&players[player_count].points) == 2)
	{
		player_count++;
		if (player_count >= MAX_PLAYERS)
			break ;
	}
	fclose(file);
	to_add = get_name(&players[player_count], &player_count, input,
			info->points);
	if (to_add)
		add_player(players, player_count);
	display_scores(players, player_count);
}
