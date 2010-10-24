##
##	Created by: Douglas von Kohorn
##	Course: CS223
##	Term: Spring 2008
##	Problem Set #5
##

# Specify which compiler to use
CC = gcc

# Specify which flags to use
CFLAGS = -std=c99 -Wall -pedantic -g -O1

# Primary target
all: main

# Rule to build executable from object file
main:	game.o util.o hexboard.o
	gcc -o game game.o util.o hexboard.o -lm

# Rule to clean up directory by removing generated files
clean:
	rm -f game *.o *.*~ *~ *.h.gch

# Dependencies which use default rule to build object from source
game.o: game.c hexboard.c hexboard.h util.h util.c
util.o: util.c util.h
hexboard.o: hexboard.c hexboard.h util.h util.c