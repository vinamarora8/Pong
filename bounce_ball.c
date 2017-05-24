#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define FRAMERATE 1000000

int main() {
	initscr();
	noecho();
	curs_set(FALSE);
	cbreak();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	int x = 0;
	int y = 2;
	int vx = 1;
	int vy = 1;
	int i=0;
	
	attron(COLOR_PAIR(1));
	mvprintw(0, 0, "  ");

	while (i<500) {
		attron(COLOR_PAIR(1));
		mvprintw(y, x, "  ");
		
		refresh();
		//fflush(stdout);
		usleep(80000);
		
		attroff(COLOR_PAIR(1));
		mvprintw(y, x, "  ");
		
		x += vx;
		y -= vy;
		
		if (x == 0 || x == 78)
			vx = -vx;

		if (y == 0 || y == 24)
			vy = -vy;

		i++;
	}

	attroff(COLOR_PAIR(1));
	getch();
	endwin();
	return 0;
	}
