#include "hanoi.h"

int main(int argc, char **argv)
{
	bool solve_arg = false;
	t_tower	towers[3];
	size_t disk_num = 3;
	if (argc >= 2)
		if (sscanf(argv[1], "%lu", &disk_num) != 1 || disk_num > MAX_HEIGHT - 1)
		{
			fprintf(stderr, "%s: error: `%s` is not a valid number of disk", argv[0], argv[1]);
			return (1);
		}
	towers_init(towers, disk_num);
	if (argc == 3 && strcmp(argv[2], "-s") == 0)
		solve_arg = true;

	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);

	int width, height;
	getmaxyx(stdscr, height, width);
	(void)height;

	int win_width = width / 3;

	WINDOW	*wins[3];
	refresh();
	for (int i = 0; i < 3; i++)
	{
		if ((wins[i] = newwin(0, win_width, 0, i * win_width)) == NULL)
			abort();
	}


	if (!solve_arg)
	{
		enum e_mode mode = MODE_SELECT_FROM;
		int from_selection = 0;
		int current = 0;
		bool running = true;
		while (running)
		{
			for (int i = 0; i < 3; i++)
			{
				enum e_highlight highlight = HIGHLIGHT_NONE;
				if (mode == MODE_SELECT_TO && i == from_selection)
					highlight |= HIGHLIGHT_FROM;
				if (i == current)
					highlight |= HIGHLIGHT_CURRENT;
				tower_put(&towers[i], wins[i], highlight);
			}

			if (towers[0].len == 0 &&
				towers[1].len == 0)
				break;

			int c;
			c = getch();

			switch (c)
			{
				case 'q':
					running = false;
					break;
				case 'j':
				case KEY_LEFT:
					current--;
					break;
				case 'k':
				case KEY_RIGHT:
					current++;
					break;
				case '\n':
					if (mode == MODE_SELECT_FROM)
					{
						if (towers[current].len == 0)
							mvprintw(0, 0, "Tower %d is empty");
						else
						{
							from_selection = current;
							mode = MODE_SELECT_TO;
						}
					}
					else if (mode == MODE_SELECT_TO)
					{
						if (!towers[current].len == 0 &&
							tower_peek(&towers[current]) < tower_peek(&towers[from_selection]))
						{
							mvprintw(0, 0, "Top disk of %d is smaller than top disk of %d",
									current, from_selection);
						}
						else
							towers_move(towers, from_selection, current);
						mode = MODE_SELECT_FROM;
					}
					break;
			}
			if (current < 0)
				current = 2;
			else if (current > 2)
				current = 0;
		}
	}
	else
		solve(towers, wins, disk_num, 0, 1, 2);

	mvaddstr(0, 0, "FINISHED: press any key to quit");
	getch();
	for (int i = 0; i < 3; i++)
		delwin(wins[3]);
	endwin();
	return 0;
}
