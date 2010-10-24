#	Created by: Douglas von Kohorn
#	Course: CS223
#	Term: Spring 2008
#	Problem Set #7

PKG_CONFIG = pkg-config
GTK_INCLUDES = $(shell $(PKG_CONFIG) --cflags gtk+-2.0)
GTK_LIBS = $(shell $(PKG_CONFIG) --libs gtk+-2.0)
CFLAGS = -std=c99 -DG_IMPLEMENT_INLINES=1 -Wall -g -O1 $(GTK_INCLUDES)
OBJ = controller.o  game.o  hexboard.o  main.o  util.o viewer.o stack.o partition.o
OBJ-TEST = game.o hexboard.o tester.o util.o stack.o partition.o
LIB =  $(GTK_LIBS) -lm
TARGETS = ghex tester

all: $(TARGETS)

ghex: $(OBJ)
	gcc -o $@ $(OBJ) $(LIB)

tester: $(OBJ-TEST)
	gcc -o $@ $(OBJ-TEST) -lm

clean:
	rm -f *~ *.*~ *.o $(TARGETS)

# Dependencies
controller.o: controller.c viewer.h game.h hexboard.h util.h
game.o: game.c util.h hexboard.h game.h
hexboard.o: hexboard.c util.h hexboard.h
main.o: main.c game.h hexboard.h controller.h viewer.h
tester.o: tester.c hexboard.h game.h util.h
util.o: util.c util.h
viewer.o: viewer.c viewer.h game.h hexboard.h
stack.o: stack.c stack.h util.c util.h
partition.o: partition.c partition.h util.c util.h game.h game.c
