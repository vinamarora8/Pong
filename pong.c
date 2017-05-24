#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define FRAMETIME 80000			// In usec
#define PADDLELENGTH 5

void initial_print();
void game_loop();

int paddle_a;
int paddle_b;
int ball_x;
int ball_y;
int ball_vx;
int ball_vy;
int user_input;
int counter;

int main() {
	
	// Initializing variables
	paddle_a = 12;
	paddle_b = 12;
	ball_x = 40;
	ball_y = 12;
	ball_vx = -1;
	ball_vy = 1;
	user_input = 0;
	counter = 0;

	WINDOW *w = initscr();
	noecho();
	curs_set(FALSE);
	cbreak();
	nodelay(w, TRUE);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	
	initial_print();
	while (user_input != 'q'){
		user_input = getch();
		game_loop();
	}
	
	// Closing screen sequence
	nocbreak();
	nodelay(w, FALSE);
	echo();
	curs_set(TRUE);
	endwin();
	return 0;
}

void game_loop() {
	if (counter == 9) {
		// Remove Ball 
		attroff(COLOR_PAIR(1));
		mvprintw(ball_y, ball_x, "  ");
		
		// Update Ball location
	
		if (ball_y == 0 || ball_y == 23)
			ball_vy = -ball_vy;
		
		if (ball_x == 2 && ball_y <= paddle_a + PADDLELENGTH/2 && ball_y >= paddle_a - PADDLELENGTH/2) {
			ball_vx = -ball_vx;
		}

		if (ball_x == 77 && ball_y <= paddle_b + PADDLELENGTH/2 && ball_y >= paddle_b + PADDLELENGTH/2)
			ball_vx = -ball_vx;
	
		ball_x += ball_vx;
		ball_y += ball_vy;
		
		if (ball_x <= 0 || ball_x >= 80) {
			user_input = 'q';
			return;
		}
	}
	counter++;
	counter %= 10;

	// Draw Ball
	attron(COLOR_PAIR(1));
	mvprintw(ball_y, ball_x, "  ");

	// Edit paddle A
	if (user_input == 'w' && paddle_a > 2){
		attroff(COLOR_PAIR(1));
		mvprintw(paddle_a + PADDLELENGTH/2, 1, "  ");
		attron(COLOR_PAIR(1));
		paddle_a--;
		mvprintw(paddle_a - PADDLELENGTH/2, 1, " ");
	}
	else if (user_input == 's' && paddle_a < 20) {
		attroff(COLOR_PAIR(1));
		mvprintw(paddle_a - PADDLELENGTH/2, 1, " ");
		attron(COLOR_PAIR(1));
		paddle_a++;
		mvprintw(paddle_a + PADDLELENGTH/2, 1, " ");
	}	
	
	// Edit paddle B 
	if (user_input == 'o' && paddle_b > 2){
		attroff(COLOR_PAIR(1));
		mvprintw(paddle_b + PADDLELENGTH/2, 79, "  ");
		attron(COLOR_PAIR(1));
		paddle_b--;
		mvprintw(paddle_b - PADDLELENGTH/2, 79, " ");
	}
	else if (user_input == 'l' && paddle_b < 20) {
		attroff(COLOR_PAIR(1));
		mvprintw(paddle_b - PADDLELENGTH/2, 79, " ");
		attron(COLOR_PAIR(1));
		paddle_b++;
		mvprintw(paddle_b + PADDLELENGTH/2, 79, " ");
	}	

	usleep(FRAMETIME/10);
	return;
}

void initial_print() {
	// Draw ball
	attron(COLOR_PAIR(1));
	mvprintw(ball_y, ball_x, "  ");

	// Draw Paddle A
	for (int i = 0; i < PADDLELENGTH; i++) 
		mvprintw(paddle_a - PADDLELENGTH/2 + i, 1, " ");

	// Draw Paddle B
	for (int i = 0; i< PADDLELENGTH; i++) 
		mvprintw(paddle_b - PADDLELENGTH/2 + i, 79, " ");
	
	refresh();
	return;
}
