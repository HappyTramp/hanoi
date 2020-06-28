#include "hanoi.h"

static uint8_t	st_tower_pop(t_tower *tower)
{
	if (tower->len == 0)
		abort();
	uint8_t top = tower->data[tower->len - 1];
	tower->len--;
	return top;
}

static void		st_tower_push(t_tower *tower, uint8_t top)
{
	if (tower->len == MAX_HEIGHT)
		abort();
	tower->data[tower->len] = top;
	tower->len++;
}

uint8_t			tower_peek(t_tower *tower)
{
	return (tower->data[tower->len - 1]);
}

void			towers_init(t_tower towers[3], size_t disk_num)
{
	memset(towers[0].data, 0, sizeof(t_tower));
	memset(towers[1].data, 0, sizeof(t_tower));
	memset(towers[2].data, 0, sizeof(t_tower));
	for (size_t i = 0; i < disk_num; i++)
		towers[0].data[i] = disk_num - i;
	towers[0].len = disk_num;
	towers[1].len = 0;
	towers[2].len = 0;
}

void			towers_move(t_tower towers[3], size_t from, size_t to)
{
	if (from > 2 || to > 2)
		abort();
	st_tower_push(&towers[to], st_tower_pop(&towers[from]));
}

void			tower_put(t_tower *tower, WINDOW *win, enum e_highlight highlight_level)
{
	int height, width;
	getmaxyx(win, height, width);

	wclear(win);
	if (highlight_level & HIGHLIGHT_FROM)
		mvwaddstr(win, 1, 1, "SELECTED");
	if (highlight_level & HIGHLIGHT_CURRENT)
		wattron(win, A_REVERSE);
	mvwvline(win, 1, width / 2, '|', height - 2);

	for (size_t i = 0; i < tower->len; i++)
	{
		int disk_width = tower->data[i] * 2 + 1;
		if (disk_width > width - 2)
		{
			disk_width = width - 5;
			wattron(win, A_BOLD);
			mvwprintw(win, height - i - 2, 0, "%2d", tower->data[i]);
			wattroff(win, A_BOLD);
		}
		mvwhline(win, height - i - 2, width / 2 - disk_width / 2, '#', disk_width);
	}
	if (highlight_level & HIGHLIGHT_CURRENT)
		wattroff(win, A_REVERSE);
	wrefresh(win);
}
