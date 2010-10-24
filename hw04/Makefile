##
##	Created by: Douglas von Kohorn
##	Course: CS223
##	Term: Spring 2008
##	Problem Set #4
##

# Specify which compiler to use
CC = gcc

# Specify which flags to use
CFLAGS = -std=c99 -Wall -pedantic -g -O1

# Primary target
all: main

# Rule to build executable from object file
main:	main.o wordfreq.o util.o flex.o
	gcc -o main main.o util.o flex.o wordfreq.o

# Rule to clean up directory by removing generated files
clean:
	rm -f main *.o *.*~ *~ *.h.gch

# Dependencies which use default rule to build object from source
main.o: main.c wordfreq.c wordfreq.h flex.h util.h
util.o: util.c util.h
flex.o: flex.c flex.h
wordfreq.o: wordfreq.c wordfreq.h util.h flex.h