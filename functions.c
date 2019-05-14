#include "functions.h"
#include "variables.h"

void draw(SDL_Renderer* renderer, int* map, Piece piece) {
	// background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	// frame
	SDL_Rect rect_frame = {0, 0, COLS*14, ROWS*14};
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawRect(renderer, &rect_frame);

	// map
	SDL_Rect rect_square = {0, 0, 12, 12};
	for (int row=0; row < ROWS; row++) {
		for (int col=0; col < COLS; col++) {
			int color = map[row*COLS+col];
			rect_square.y = row*14 + 1;
			rect_square.x = col*14 + 1;
			if (color != 0) {
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderDrawRect(renderer, &rect_square);
			}
		}
	}

	for (int row=0; row < 4; row++) {
		for (int col=0; col < 4; col++) {
			int color = piece.shape[row][col];
			rect_square.y = (row + piece.y)*14 + 1;
			rect_square.x = (col + piece.x)*14 + 1;
			if (color != 0) {
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderDrawRect(renderer, &rect_square);
			}
		}
	}
	SDL_RenderPresent(renderer);
}

//to rotate the tile
int rotate(Piece* piece) {
	Piece tmp;
	memcpy(&tmp, piece, sizeof(tmp));
	int n = 3;
	if (piece->id == 0) n = 4; // line
	for (int row=0; row < n; row++) {
		for (int col=0; col < n; col++) {
			piece->shape[row][col] = tmp.shape[n - col - 1][row];
		}
	}
	return 0;
}

//to see if two tiles collides with each other or collides the bound 
int colliding (const int *map, const Piece* piece) {
	for (int row=0; row < 4; row++) {
		for (int col=0; col < 4; col++) {
			int mapx = piece->x + col;
			int mapy = piece->y + row;
			if (mapy < 0 ||(piece->shape[row][col] &&
				 (map[mapy*COLS+mapx] ||
				   mapx < 0 || mapy >= ROWS || mapx >= COLS))) {
				printf("collision\n");
				return 1;
			}
		}
	}
	return 0;
}

//to place tiles onto each other 
int place_on_map(int *map, Piece* piece) {
	for (int row=0; row < 4; row++) {
		for (int col=0; col < 4; col++) {
			int mapx = piece->x + col;
			int mapy = piece->y + row;
			int tile = piece->shape[row][col];
			if (tile) {
				map[mapy*COLS+mapx] = tile;
			}
		}
	}
	return 0;
}

//randomly get a piece of tile 
void get_piece(Piece* piece) {
	piece->id = random() % 7;
	memcpy(piece->shape, shapes[piece->id], sizeof(piece->shape));
}


void drop_line(int *map, int n) {
	for (int row=n; row > 0; row--) {
		if (row == ROWS) continue;
		memcpy(&map[row*COLS], &map[(row-1)*COLS], sizeof(int)*COLS);
	}
}

//to clear a line that is full
int clear_lines(int *map) {
	int n_lines = 0;
	for (int row=0; row < ROWS; row++) {
		int good = 1;
		for (int col=0; col < COLS; col++) {
			if (!map[row*COLS+col]) {
				good = 0;
			}
		}
		if (good) {
			drop_line(map, row);
			n_lines++;
		}
	}
	return n_lines;
}

//automatically fall down a little every lap time
int step(int *map, Piece *piece, int *cleared_lines) {
	piece->y += 1;
	if (!colliding(map, piece)) {
		return 0;
	}
	piece->y -= 1;
	place_on_map(map, piece);
	*cleared_lines = clear_lines(map);

	// new piece
	piece->x = (COLS/2-2);
	piece->y = 0;
	get_piece(piece);

	if (colliding(map, piece)) {
		return 2;
	}
	return 1;
}

//to handle keyboard events
int handle_input(KeyTable* key) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return 1;
		}
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_RIGHT:
					key->right = 1;
					break;
				case SDLK_LEFT:
					key->left = 1;
					break;
				case SDLK_UP:
					key->rot = 1;
					break;
				case SDLK_SPACE:
					key->drop = 1;
					break;
				case SDLK_DOWN:
					key->fast = 1;
					break;
			}
		}
		if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
				case SDLK_RIGHT:
					key->right = 0;
					break;
				case SDLK_LEFT:
					key->left = 0;
					break;
				case SDLK_UP:
					key->rot = 0;
					break;
				case SDLK_DOWN:
					key->fast = 0;
					break;
			}
		}
	}
	return 0;
}

int gameover() {
	puts("game over");
	return 0;
}
