#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define FRAMETIME 80000			// In usec
#define PADDLELENGTH 5

void initial_print();
void draw_scoreline();
int game_loop();

int paddle_a;
int paddle_b;
int ball_x;
int ball_y;
int ball_vx;
int ball_vy;
int user_input;
int counter;
int ball_delay;
int score_a;
int score_b;

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
	ball_delay = 10;
	score_a = 0;
	score_b = 0;
	
	WINDOW *w = initscr();
	noecho();
	curs_set(FALSE);
	cbreak();
	nodelay(w, TRUE);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	
	STARTGAME: while (score_a < 10 && score_b < 10 && user_input != 'q'){
		initial_print();
		draw_scoreline();
		int loop;
		while (user_input != 'q'){
			user_input = getch();
			loop = game_loop();
			if (loop == 'a'){
				score_a++;
				draw_scoreline();
				break;
			}
			else if (loop == 'b'){
				score_b++;
				draw_scoreline();
				break;
			}
		}
		usleep(1000000);
	}
	// Closing screen sequence
	nocbreak();
	nodelay(w, FALSE);
	echo();
	curs_set(TRUE);
	endwin();
	return 0;
}

int game_loop() {
	
	// Edit paddle A
	if (user_input == 'w' && paddle_a > 4){
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
	if (user_input == 'o' && paddle_b > 4){
		attroff(COLOR_PAIR(1));
		mvprintw(paddle_b + PADDLELENGTH/2, 78, "  ");
		attron(COLOR_PAIR(1));
		paddle_b--;
		mvprintw(paddle_b - PADDLELENGTH/2, 78, " ");
	}
	else if (user_input == 'l' && paddle_b < 20) {
		attroff(COLOR_PAIR(1));
		mvprintw(paddle_b - PADDLELENGTH/2, 78, " ");
		attron(COLOR_PAIR(1));
		paddle_b++;
		mvprintw(paddle_b + PADDLELENGTH/2, 78, " ");
	}	
	
	// Handling the ball occasionally
	if (counter == ball_delay-1) {
		// Remove Ball 
		attroff(COLOR_PAIR(1));
		mvprintw(ball_y, ball_x, "  ");
		
		// Update Ball location
		if (ball_y <= 2 || ball_y >= 23)
			ball_vy = -ball_vy;
		
		if (ball_x == 2 && ball_y <= paddle_a + PADDLELENGTH/2 && ball_y >= paddle_a - PADDLELENGTH/2) 
			ball_vx = -ball_vx;

		if (ball_x == 76 && ball_y <= paddle_b + PADDLELENGTH/2 && ball_y >= paddle_b - PADDLELENGTH/2)
			ball_vx = -ball_vx; 
	
		ball_x += ball_vx;
		ball_y += ball_vy;
		
		if (ball_x <= 0)
			return 'b';
		else if (ball_x >= 80)
			return 'a';
	}
	counter++;
	counter %= ball_delay;

	// Draw Ball
	attron(COLOR_PAIR(1));
	mvprintw(ball_y, ball_x, "  ");

	

	usleep(FRAMETIME/10);
	return 0;
}

void initial_print() {
	clear();
	
	// Initializing Values
	paddle_a = 12;
	paddle_b = 12;
	ball_x = 40;
	ball_y = 12;
	ball_vx = -1;
	ball_vy = 1;
	user_input = 0;
	counter = 0;

	
	// Draw ball
	attron(COLOR_PAIR(1));
	mvprintw(ball_y, ball_x, "  ");

	// Draw Paddle A
	for (int i = 0; i < PADDLELENGTH; i++) 
		mvprintw(paddle_a - PADDLELENGTH/2 + i, 1, " ");

	// Draw Paddle B
	for (int i = 0; i< PADDLELENGTH; i++) 
		mvprintw(paddle_b - PADDLELENGTH/2 + i, 78, " ");
	
	refresh();
	return;
}

void draw_scoreline() {
	// Drawing user names
	attroff(COLOR_PAIR(1));
	char *a = malloc(10);
	sprintf(a, "User A: %d", score_a);
	mvprintw(0, 1, a);
	sprintf(a, "User B: %d", score_b);
	mvprintw(0, 80-11, a);
	mvprintw(0, 39, "||");

	// Draw lower border
	attron(COLOR_PAIR(1));
	for (int i = 0; i< 80; i++)
		mvprintw(1, i, " ");
	
	refresh();
	return;
}
