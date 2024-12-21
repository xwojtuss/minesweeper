#include "minesweeper.h"

// can flip the flag
void	change_flag(short *info)
{
	*info ^= FLAGED;
}

// will not flip, only set
void	set_bomb(short *info)
{
	*info |= BOMB;
}

bool	is_revealed(short info)
{
	return ((info & REVEALED) / REVEALED);
}

bool	is_flagged(short info)
{
	return ((info & FLAGED) / FLAGED);
}

bool	is_bomb(short info)
{
	return ((info & BOMB) / BOMB);
}
