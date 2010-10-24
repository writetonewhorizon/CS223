# Michael J. Fischer
# CPSC 223b, Spring 2008

# Specify which compiler to use
CC = gcc

# Specify which flags to use
CFLAGS = -std=c99 -Wall -pedantic -g -O1

# Primary target
all: unodx1

# Rule to build executable from object file
unodx1:	unodx1.o util.o
	gcc -o unodx1 unodx1.o util.o

# Rule to clean up directory by removing generated files
clean:
	rm -f unodx1 unodx1.o util.o util.h.gch *.*~ *~

# Dependencies which use default rule to build object from source
unodx1.o: unodx1.c util.h
util.o: util.c util.h