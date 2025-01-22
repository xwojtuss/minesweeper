#ifndef MINESWEEPER_H
# define MINESWEEPER_H

# include <errno.h>
# include <fcntl.h>
# include <getopt.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <time.h>
# include <unistd.h>

# define BOMB (1 << BOMB_BIT)
# define FLAGED (1 << FLAGED_BIT)
# define REVEALED (1 << REVEALED_BIT)
# define COUNT (7 << COUNT_START_BIT)

# define BOMB_BIT 0
# define FLAGED_BIT 1
# define REVEALED_BIT 2
# define COUNT_START_BIT 3
# define COUNT_END_BIT 5

# define BUFFER_SIZE 64
# define COLOR_BOLD "\e[1m"
# define COLOR_OFF "\e[m"

# define MAX_PLAYERS 100
# define MAX_NAME_LEN 128
# define LEADERBOARD_FILE ".leaderboard"

# define BIN_NAME "minesweeper"

/*

Komórka to char, gdzie najmniej znaczący bit oznacza:
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

typedef struct s_player
{
	char	name[MAX_NAME_LEN];
	int		points;
}			t_player;

typedef struct s_game_info
{
	char	difficulty;
	int		cols;
	int		rows;
	int		mines;
	int		instructions;
	int		points;
}			t_game_info;

// allocation.c:

void		init_info(t_game_info *info);
void		free_grid(char **grid, int cols);
char		**create_array(unsigned int cols, unsigned int rows);

// errors.c

void		err_usage(char *message);
void		err(char *message);
void		print_usage(void);
void		err_close_free(char *message, FILE *to_close, char **grid,
				int cols);
void		err_close_perror(char *message, FILE *to_close);
void		err_close(char *message, FILE *to_close);

// generate_map.c

bool		bomb_check(char **grid, int r, int c, t_game_info *info);
void		place_bombs(char **grid, t_game_info *info, int r, int c);
void		add_count_surround(char **grid, int r, int c, t_game_info *info);

// get_type.c

bool		is_flagged(char info);
bool		is_revealed(char info);
bool		is_bomb(char info);

// leaderboard.c

void		get_leaderboard(t_game_info *info, FILE *input);

// parsing.c

void		get_leaderboard(t_game_info *info, FILE *input);
FILE		*get_input(int argc, char **argv);
bool		is_valid(char *token, char from, char to);
void		get_x_y(FILE *input, char buffer[BUFFER_SIZE], t_game_info *info);
int			get_size(FILE *input, t_game_info *info);
int			load_map(FILE *input, char **grid, t_game_info *info);

// print.c

void		print_score(t_game_info *info);
void		print_end_game(char **grid, t_game_info *info, bool is_success);
void		print_diff_levels(void);
void		print_field(char **grid, int rows, int cols, bool is_finished);

// reveal.c

int			reveal_grid(char **grid, int r, int c, t_game_info *info);

// set_type.c

void		reveal(char *info);
void		change_flag(char *info);
void		set_bomb(char *info);
void		add_count(char *info);

// start_game.c

void		first_move(FILE *input, char **grid, t_game_info *info);
bool		start_game(FILE *input, char **grid, t_game_info *info);

#endif /* MINESWEEPER_H */
