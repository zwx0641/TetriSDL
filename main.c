
#include "functions.h"

long now() {
 return SDL_GetTicks();
}

int main() {
	srandom(time(NULL));
	int step_time = 500; // fall down a tile every step_time
	int input_step_time = 1000/15; // apply input at 15 fps
	long next_step = now() + step_time;
	long next_input_step = now() + input_step_time;
	int score = 0;
	int cleared_lines;

	int map[ROWS*COLS] = {0};
	Piece piece = {{0}, (COLS/2-2), 0, 0};
	get_piece(&piece);

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
			"Tetris",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			640,                               // width, in pixels
			480,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags
			);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	KeyTable key_table = {0};


//game procedure
	while (1) {
		if (handle_input(&key_table) == 1) {
			break;
		}
		if (now() > next_input_step) {
			next_input_step = now() + input_step_time;
			if (key_table.right) {
				piece.x += 1;
				if (colliding(map, &piece)) {
					piece.x -= 1;
				}
			}
			if (key_table.left) {
				piece.x -= 1;
				if (colliding(map, &piece)) {
					piece.x += 1;
				}
			}
			if (key_table.rot) {
				Piece bak;
				memcpy(&bak, &piece, sizeof(bak));
				rotate(&piece);
				if (colliding(map, &piece)) {
					memcpy(&piece, &bak, sizeof(piece));
				}
				key_table.rot = 0; // can't hold rot
			}
		}
		if (key_table.drop || now() > next_step -(key_table.fast ? (7 * step_time / 8) : 0)) {
			int step_r = step(map, &piece, &cleared_lines);
			if (step_r) {
				if (step_time > 120) {
					step_time -= 20;
				}
				key_table.drop = 0;
			}
			if (step_r == 2) {
				gameover();
				break;
			}
			next_step = now() + step_time;
		}
		// score
		switch (cleared_lines) {
			case 1:
				score += 40;
				break;
			case 2:
				score += 100;
				break;
			case 3:
				score += 300;
				break;
			case 4:
				score += 1200;
				break;
		}
		// drawing
		draw(renderer, map, piece);
	}
	printf("Your score is %d\n", score);
//end:
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
