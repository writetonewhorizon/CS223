#
#	Created by: Douglas von Kohorn
#	Course: CS223
#	Term: Spring 2008
#	Problem Set #2
#
# Simple Makefile

# Specify which compiler to use
CC = gcc

# Specify which flags to use
CFLAGS = -g -Wall -O1 -std=c99 -pedantic

# Rule to build executable from object file
readpair:	cake.o
	gcc -o cake cake.o -lm

# Rule to clean up directory by removing generated files
clean:
	rm -f cake cake.o *~ .*~

# Dependencies which use default rule to build object from source
cake.o: cake.c