# Makefile for 'indexer' module
#
# Charlie Baker, May 2023

OBJS = querier.o fuzzquery.o
LIBS = ../common/common.a ../libcs50/libcs50-given.a
L = 

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make

all: querier fuzzquery

querier: querier.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

fuzzquery: fuzzquery.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Dependencies: object files
querier.o: 
fuzzquery.o:

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: test valgrind clean all querier fuzzquery

# run test script
test: testing.sh
	./testing.sh 

# run valgrind with test script
valgrind:
	$(VALGRIND) ./querier ../crawler/data/toscrape/depth1 ../crawler/data/toscrape/depth1.index

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f core
	rm -f querier
	rm -f fuzzquery
