#include "hanoi.h"

void solve(t_tower towers[3], WINDOW *wins[3],
		   int n, int from, int via, int to)
{
	if (n == 0)
		return;
	solve(towers, wins, n - 1, from, to, via);
	towers_move(towers, from, to);

	for (int i = 0; i < 3; i++)
		tower_put(&towers[i], wins[i], HIGHLIGHT_NONE);
	usleep(1000);

	solve(towers, wins, n - 1, via, from, to);
}
