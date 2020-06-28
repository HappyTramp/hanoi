#ifndef HANOI_H
# define HANOI_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include <string.h>

# include <ncurses.h>

# define MAX_HEIGHT 128

enum e_mode
{
	MODE_SELECT_FROM,
	MODE_SELECT_TO,
};


typedef struct
{
	uint8_t	data[MAX_HEIGHT];
	size_t	len;
}			t_tower;

enum e_highlight
{
	HIGHLIGHT_NONE    = 0,
	HIGHLIGHT_FROM    = 1 << 0,
	HIGHLIGHT_CURRENT = 1 << 1,
};

void	towers_init(t_tower towers[3], size_t disk_num);
void	towers_move(t_tower towers[3], size_t from, size_t to);
void	tower_put(t_tower *tower, WINDOW *win, enum e_highlight highlight_level);
uint8_t	tower_peek(t_tower *tower);

void	solve(t_tower towers[3], WINDOW *wins[3],
				int n, int from, int via, int to);

#endif
