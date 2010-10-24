# Michael J. Fischer
# CPSC 223b, Spring 2008
# Problem set 9: Huffman code

# Specify which compiler to use
CC = gcc

# Specify options to give to the compiler when translating source to object
# -g		Generate debugging code, for use with gdb
# -Wall		Enable all warnings
# -O1		First level of optimization
# -std=c99	Adhere to C99 language standard
# -pedantic	Reject programs using non-standard extensions

CFLAGS = -g -Wall -O1 -std=c99 -pedantic

# Object files comprising the project
OBJ = util.o bitstring.o codetree.o codetable.o ibitstream.o obitstream.o

# Targets
TARGETS = pfxenc pfxdec

all: $(TARGETS)
	
pfxenc: pfxenc.o $(OBJ)
	gcc -o $@ $(OBJ) pfxenc.o

pfxdec: pfxdec.o $(OBJ)
	gcc -o $@ $(OBJ) pfxdec.o
	
.PHONY: clean depend
clean:
	rm -f $(TARGETS) *.o

depend:
	(sed -n '1,/^# Dependencies/p' Makefile; $(CC) -MM *.c) > Makefile.tmp
	rm Makefile
	mv Makefile.tmp Makefile

# Dependencies
bitstring.o: bitstring.c util.h bitstring.h
codetable.o: codetable.c util.h codetree.h bitstring.h codetable.h \
  ibitstream.h obitstream.h
codetree.o: codetree.c util.h codetree.h bitstring.h codetable.h \
  ibitstream.h obitstream.h
heap.o: heap.c heap.h util.h
ibitstream.o: ibitstream.c util.h bitstring.h ibitstream.h
obitstream.o: obitstream.c util.h bitstring.h obitstream.h
pfxdec.o: pfxdec.c bitstring.h util.h ibitstream.h codetree.h codetable.h \
  obitstream.h
pfxenc.o: pfxenc.c bitstring.h codetable.h util.h obitstream.h
util.o: util.c util.h
