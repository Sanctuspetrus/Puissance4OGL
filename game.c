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

int validateHauteur(Game*);
int validateLargeur(Game*);
int validateLongueur(Game*);
int validateDigonale(Game*);

const char NEUTRAL = 0;
const char WHITE = 1;
const char BLACK = -1;
const char WIN_WHITE = 1 * GAME_SIZE;
const char WIN_BLACK = -1 * GAME_SIZE;

// int main(int argc, char const *argv[]) {
// 	Game* game = malloc(sizeof(Game));
// 	Cursor* cursor;
// 	int stop = 0;
// 	char input;
//
// 	initGame(game);
// 	cursor = game->cursor;
//
// 	printGame(*game);
// 	while(!stop){
// 		input = getc(stdin);
// 		getchar();
// 		switch (input) {
// 			case 'x': stop = 1;
// 			break;
// 			case 'd': cursorRight(cursor);
// 			break;
// 			case 'q': cursorLeft(cursor);
// 			break;
// 			case 'z': cursorBack(cursor);
// 			break;
// 			case 's': cursorFront(cursor);
// 			break;
// 			case 'e': putBallDown(game);
// 			break;
// 			default:
// 			printf("cassé\n");
// 			input = 0;
// 			break;
// 		}
// 		printGame(*game);
// 		if (validateGame(game) != 0) {
// 			printf("Victoire!\n");
// 			stop = 1;
// 		}
// 	}
//
// 	return 0;
// }


//	GAME
void printGame(Game game){
	int x,y,z;
	char token = 'o';
	for (z = 0; z < GAME_SIZE; z++) {
		for (y = 0; y < GAME_SIZE; y++) {
			for (x = 0; x < GAME_SIZE; x++) {
				if(getPosColorAt(game, x, y, z) == WHITE) printf(ACYELLOW);
				if(getPosColorAt(game, x, y, z) == BLACK) printf(ACBLUE);
				if(isCursorAt(*(game.cursor), x, y, z)) printf(ACGREEN);
				printf("%c", token);
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
	setCursorAt(game->cursor, 0, 0, 0);
	setWhite(game->cursor);
	for (z = 0; z < GAME_SIZE; z++) {
		for (y = 0; y < GAME_SIZE; y++) {
			for (x = 0; x < GAME_SIZE; x++) {
				game->matrice[x][y][z] = NEUTRAL;
			}
		}
	}
}

int validateGame(Game* game){
	int res = 0;
	if ((res = validateHauteur(game))) { return res; }
	if ((res = validateLargeur(game))) { return res; }
	if ((res = validateLongueur(game))) { return res; }
	if ((res = validateDigonale(game))) { return res; }
	return res;
}
int validateHauteur(Game* game){
	int x,y,z;
	int count = 0;
	/*
	Pour chaque colonnes j'additionne tout les y, si le total correspond à une victoire j'arrête
	*/
	for (z = 0; z < GAME_SIZE; z++) {
		for (x = 0; x < GAME_SIZE; x++) {
			count = 0;
			for (y = 0; y < GAME_SIZE; y++) {
				count += getPosColorAt(*game, x, y, z);
			}
			if (count == WIN_WHITE || count == WIN_BLACK) {
				printf("yes\n");
				return count;
			}
		}
	}
	return 0;
}
int validateLargeur(Game* game){
	int x,y,z;
	int count = 0;
	/*
	Pour chaque lignes horizontales j'additionne tout les x, si le total correspond à une victoire j'arrête
	*/
	for (y = 0; y < GAME_SIZE; y++) {
		for (z = 0; z < GAME_SIZE; z++) {
			count = 0;
			for (x = 0; x < GAME_SIZE; x++) {
				count += getPosColorAt(*game, x, y, z);
			}
			if (count == WIN_WHITE || count == WIN_BLACK) {
				printf("yes\n");
				return count;
			}
		}
	}
	return 0;
}
int validateLongueur(Game* game){
	int x,y,z;
	int count = 0;
	/*
	Pour chaque lignes verticales j'additionne tout les z, si le total correspond à une victoire j'arrête
	*/
	for (y = 0; y < GAME_SIZE; y++) {
		for (x = 0; x < GAME_SIZE; x++) {
			count = 0;
			for (z = 0; z < GAME_SIZE; z++) {
				count += getPosColorAt(*game, x, y, z);
			}
			if (count == WIN_WHITE || count == WIN_BLACK) {
				printf("yes\n");
				return count;
			}
		}
	}
	return 0;
}
int validateDigonale(Game* game){
	return 0;
}

void switchColor(Game* game){
	if (isCursorWhite(*(game->cursor))) {
		setBlack(game->cursor);
	} else {
		setWhite(game->cursor);
	}
}
/**
* Dépose une boule à l'emplacement du curseur
* La boule glisse si il n'y pas de boules en-dessous
* Aucune action si l'emplacement est déjà occupé par une boule
**/
int putBallDown(Game* game){
	int x = game->cursor->x;
	int y = game->cursor->y;
	int z = game->cursor->z;

	if (getPosColor(*game) != NEUTRAL) {
		return EXIT_FAILURE;
	}
	y = fall(*game);
	putBallAt(game, x, y, z);
	switchColor(game);
	return EXIT_SUCCESS;
}
/**
*
*
**/
int fall(Game game){
	int x = game.cursor->x;
	int y = game.cursor->y;
	int z = game.cursor->z;

	while (y+1<GAME_SIZE && getPosColorAt(game,x,y+1,z) == NEUTRAL){
		y++;
	}

	return y;
}

/**
* Retourne la couleur de la matrice
* à la position du curseur
**/
int getPosColor(Game game){
	return game.matrice[game.cursor->x][game.cursor->y][game.cursor->z];
}
/**
* Retourne la couleur de la matrice
* à la position (x, y, z)
**/
int getPosColorAt(Game game, int x, int y, int z){
	return game.matrice[x][y][z];
}
/**
* Définit la couleur de la matrice
* à la position (x, y, z)
**/
void putBallAt(Game* game, int x, int y, int z){
	game->matrice[x][y][z] = game->cursor->color;
}

int getColor(Game game){
	return game.cursor->color;
}

//	CURSOR	///////////////////////////////////////////

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
int isCursorAt(Cursor cur, int x, int y, int z){
	if(cur.x == x && cur.y == y && cur.z == z)
	return 1;
	return 0;
}

void setCursorColor(Cursor* cur, char color){
	cur->color = color;
}
void setWhite(Cursor* cur){
	setCursorColor(cur, WHITE);
}
void setBlack(Cursor* cur){
	setCursorColor(cur, BLACK);
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
