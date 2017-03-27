
#define GAME_SIZE 4

const char NEUTRAL = 0;
const char WHITE = 1;
const char BLACK = 2;

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
void initGame(Game*);
void validateGame(Game*);
void printGame(Game*);
void switchColor(Game*);
void putDown(Game*);

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
