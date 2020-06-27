#include "hanoi.h"

int main()
{
	initscr();
	noecho();
	cbreak();

	int width, height;
	getmaxyx(stdscr, height, width);
	(void)height;

	int win_width = width / 3;

	WINDOW	*wins[3];
	for (int i = 0; i < 3; i++)
	{
		refresh();
		if ((wins[i] = newwin(0, win_width, 0, i * win_width)) == NULL)
			abort();
		box(wins[i], 0, 0);
		/* wrefresh(wins[i]); */
	}

	t_tower	towers[3];
	towers_init(towers, 3);

	int from_selection = 0;
	int to_selection = 1;
	bool mode_from = true;
	bool running = true;
	while (running)
	{
		for (int i = 0; i < 3; i++)
		{
			int highlight_level = 0;
			if (i == from_selection)
				highlight_level = 1;
			tower_put(&towers[i], wins[i], highlight_level);
		}

		char c;
		c = getch();

		int selection = mode_from ? from_selection : to_selection;
		switch (c)
		{
			case 'q':
				running = false;
				break;
			case 'j':
				selection--;
				break;
			case 'k':
				selection++;
				break;
			case '\n':
				if (mode_from)
					from_selection = selection;
				else
					to_selection = selection;
				if (!mode_from)
					towers_move(towers, from_selection, to_selection);
				mode_from = !mode_from;
				break;
		}
		selection %= 3;
		mvprintw(0, 0, "%d", selection);
		refresh();
	}

	/* refresh(); */

	for (int i = 0; i < 3; i++)
		delwin(wins[3]);
	endwin();
	return 0;
}
