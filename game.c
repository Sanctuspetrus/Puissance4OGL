#include <stdlib.h>
#include <stdio.h>
#include "game.h"

#define ACRED     "\x1b[31m"
#define ACGREEN   "\x1b[32m"
#define ACYELLOW  "\x1b[33m"
#define ACBLUE    "\x1b[34m"
#define ACMAGENTA "\x1b[35m"
#define ACCYAN    "\x1b[36m"
#define ACRESET   "\x1b[0m"

int main(int argc, char const *argv[]) {
	Game* game = malloc(sizeof(Game));
	Cursor* cursor;
	int stop = 0;
	char input;

	initGame(game);
	cursor = game->cursor;

	while(!stop){
		printGame(game);
		input = getc(stdin);
		getchar();
		switch (input) {
			case 'x': stop = 1;
			break;
			case 'd': cursorRight(cursor);
			break;
			case 'q': cursorLeft(cursor);
			break;
			case 'z': cursorBack(cursor);
			break;
			case 's': cursorFront(cursor);
			break;
			default:
			break;
		}
	}

	return 0;
}

void printGame(Game* game){
	int x,y,z;
	for (z = 0; z < GAME_SIZE; z++) {
		for (y = 0; y < GAME_SIZE; y++) {
			for (x = 0; x < GAME_SIZE; x++) {
				if(isCursorWhite(*(game->cursor))) printf(ACYELLOW);
				if(isCursorBlack(*(game->cursor))) printf(ACBLUE);
				if(isCursorAt(*(game->cursor), x, y, z)) printf(ACGREEN);
				printf("%d", game->matrice[x][y][z]);
				printf(ACRESET);
			}
			printf(" ");
		}
		printf("\n");
	}
}

void initGame(Game* game){
	int x,y,z;

	game->cursor = malloc(sizeof(Cursor));
	for (z = 0; z < GAME_SIZE; z++) {
		for (y = 0; y < GAME_SIZE; y++) {
			for (x = 0; x < GAME_SIZE; x++) {
				game->matrice[x][y][z] = NEUTRAL;
			}
		}
	}
}

void setCursorAt(Cursor* cur, int x, int y, int z){
	if(x>0 && x<GAME_SIZE) cur->x = x;
	if(y>0 && y<GAME_SIZE) cur->y = y;
	if(z>0 && z<GAME_SIZE) cur->z = z;
}

void cursorRight(Cursor* cur){
	if(cur->x<GAME_SIZE-1) cur->x++;
}
void cursorLeft(Cursor* cur){
	if(cur->x>0) cur->x--;
}
void cursorFront(Cursor* cur){
	if(cur->z<GAME_SIZE-1) cur->z++;
}
void cursorBack(Cursor* cur){
	if(cur->z>0) cur->z--;
}


int isCursorWhite(Cursor cur){
	return cur.color == WHITE;
}
int isCursorBlack(Cursor cur){
	return cur.color == BLACK;
}
int isCursorNeutral(Cursor cur){
	return cur.color == NEUTRAL;
}

int isCursorAt(Cursor cur, int x, int y, int z){
	if(cur.x == x && cur.y == y && cur.z == z)
	return 1;
	return 0;
}
