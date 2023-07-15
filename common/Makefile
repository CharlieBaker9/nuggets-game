# Makefile for 'common' module
#
# Charlie Baker, April 2023

OBJS = pagedir.o index.o  word.o
LIB = common.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50
CC = gcc
MAKE = make

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files
pagedir.o: pagedir.h
index.o: index.h
word.o: word.h

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o *.gch
	rm -f settest
	rm -f core
