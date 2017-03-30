#ifndef GAME_H
#define GAME_H

#define GAME_SIZE 4

#define NEUTRAL 0
#define WHITE 1
#define BLACK -1
#define WIN_WHITE 1 * GAME_SIZE
#define WIN_BLACK -1 * GAME_SIZE


typedef struct _cursor {
	int x;	// Positon du curseur sur X
	int y;	// Positon du curseur sur Y
	int z;	// Positon du curseur sur Z
	char color;
} Cursor;

typedef struct _game {
	char matrice[GAME_SIZE][GAME_SIZE][GAME_SIZE];	// Matrice de la position des boules
	Cursor* cursor;
} Game;


// GAME
void initGame(Game**);
void resetGame(Game*);
int validateGame(Game*);
void printGame(Game);
int getColor(Game);
int putBallDown(Game*);
int getPosColor(Game); // Couleur à la position du curseur
int getPosColorAt(Game, int x, int y, int z); // Couleur à la position donnée
void putBallAt(Game*, int x, int y, int z); // Couleur à la position donnée
int fall(Game); // Position la plus basse en-dessous du curseur
// CURSOR
char getCursorColor(Cursor*);
void setCursorColor(Cursor*, char);
void setWhite(Cursor*);
void setBlack(Cursor*);
int isCursorWhite(Cursor);
int isCursorBlack(Cursor);
int isCursorNeutral(Cursor);

void setCursorAt(Cursor*, int x, int y, int z);
void cursorRight(Cursor*);	// x++
void cursorLeft(Cursor*);	// x--
void cursorBack(Cursor*);	// z++
void cursorFront(Cursor*);	// z--
int isCursorAt(Cursor, int x, int y, int z);

#endif
