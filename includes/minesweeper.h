#ifndef MINESWEEPER_H
# define MINESWEEPER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>

# define BOMB (1 << BOMB_BIT)
# define FLAGED (1 << FLAGED_BIT)
# define REVEALED (1 << REVEALED_BIT)
# define COUNT (7 << COUNT_START_BIT)

# define BOMB_BIT 0
# define FLAGED_BIT 1
# define REVEALED_BIT 2
# define COUNT_START_BIT 3
# define COUNT_END_BIT 4

// do uporzadkowania:

// get_set_type.c
void	change_flag(short *info);
void	set_bomb(short *info);
bool	is_flagged(short info);
bool	is_revealed(short info);
bool	is_bomb(short info);

// errors.c
void	err_usage(char *message);
void	err(char *message);
void	print_usage(void);

// allocation.c:

void	free_grid(short **grid, int cols);
short	**create_array(unsigned int rows, unsigned int cols);

#endif /* MINESWEEPER_H */