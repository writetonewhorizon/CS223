#	Created by: Douglas von Kohorn
#	Course: CS223
#	Term: Spring 2008
#	Problem Set #6

CFLAGS = -std=c99 -Wall -pedantic -g -O1 $(shell pkg-config --cflags gtk+-2.0)
OBJ = controller.o  game.o  hexboard.o  main.o  util.o  viewer.o stack.o
LIB =  $(shell pkg-config --libs gtk+-2.0) -lm

all: ghex

ghex: $(OBJ)
	gcc -o $@ $(OBJ) $(LIB)

clean:
	rm -f *.o ghex .*~ *~

# Dependencies
controller.o: controller.c viewer.h game.h hexboard.h util.h
game.o: game.c util.h hexboard.h game.h
hexboard.o: hexboard.c util.h hexboard.h
main.o: main.c game.h hexboard.h controller.h viewer.h
util.o: util.c util.h
stack.o: stack.c stack.h game.h
viewer.o: viewer.c viewer.h game.h hexboard.h
