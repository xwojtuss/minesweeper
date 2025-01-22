#include "minesweeper.h"

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
