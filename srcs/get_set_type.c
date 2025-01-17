#include "minesweeper.h"

// will not flip
void	reveal(char *info)
{
	*info |= REVEALED;
}

// can flip the flag
void	change_flag(char *info)
{
	*info ^= FLAGED;
}

// will not flip, only set
void	set_bomb(char *info)
{
	*info |= BOMB;
}

void	add_count(char *info)
{
	*info += (1 << COUNT_START_BIT);
}

bool	is_revealed(char info)
{
	return ((info & REVEALED) / REVEALED);
}

bool	is_flagged(char info)
{
	return ((info & FLAGED) / FLAGED);
}

bool	is_bomb(char info)
{
	return ((info & BOMB) / BOMB);
}
