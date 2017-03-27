CC=gcc
CFLAGS=-I.

LIBS=-lGL -lglut -lGLU

DEPS=funct.h

OBJ=projet.o funct.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

puissance4: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core
