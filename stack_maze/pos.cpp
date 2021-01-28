#include "pos.h"

int offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

Position move_to(Position pos, int dir) {
	Position next;
	next.x = pos.x + offset[dir][0];
	next.y = pos.y + offset[dir][1];
	return next;
}
