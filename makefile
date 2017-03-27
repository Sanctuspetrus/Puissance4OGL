CC=gcc
CFLAGS=-I.

LIBS=-lGL -lglut -lGLU

DEPS=funct.h game.h

OBJ=projet.o funct.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

puissance4: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

game: game.o
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core
