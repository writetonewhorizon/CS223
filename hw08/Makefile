##
##	Created by: Douglas von Kohorn
##	Course: CS223
##	Term: Spring 2008
##	Problem Set #8
##

# Specify which compiler to use
CC = gcc

# Specify which flags to use
CFLAGS = -std=c99 -Wall -pedantic -g -O1

# Primary target
all: main

# Rule to build executable from object file
main:	main.o util.o hamming.o
	gcc -o ham main.o util.o hamming.o -lm

# Rule to clean up directory by removing generated files
clean:
	rm -f ham *.o *.*~ *~ *.h.gch

# Dependencies which use default rule to build object from source
main.o: main.c util.h util.c
util.o: util.c util.h
hamming.o: hamming.c hamming.h util.c util.h