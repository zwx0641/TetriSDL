
#include <SDL.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define ROWS 30
#define COLS 10

//define a structure for a tile
typedef struct {
	int shape[4][4];
	int x;
	int y;
	int id;
} Piece;

//operations
typedef struct {
	int right;
	int left;
	int rot;
	int rotb;
	int drop;
	int fast;
} KeyTable;

void draw(SDL_Renderer* renderer, int* map, Piece piece);

int rotate(Piece* piece);

int colliding (const int *map, const Piece* piece);

int place_on_map(int *map, Piece* piece);

void get_piece(Piece* piece);

void drop_line(int *map, int n);

int clear_lines(int *map);

int step(int *map, Piece *piece, int *cleared_lines);

int handle_input(KeyTable* key);

int gameover();
