# Makefile for 'indexer' module
#
# Charlie Baker, May 2023

OBJS = indexer.o indextest.o
LIBS = ../common/common.a ../libcs50/libcs50-given.a
L = 

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make

all: indexer indextest

indexer: indexer.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indextest: indextest.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Dependencies: object files
indexer.o: 
indextest.o:

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: test valgrind clean all indexer indextest

# run test script
test: testing.sh
	./testing.sh 

# run valgrind with test script
valgrind:
	$(VALGRIND) ./indexer ../crawler/data/letters/depth10 ../crawler/data/letters/depth10.index
	$(VALGRIND) ./indextest ../../shared/tse/indices/toscrape-1.ndx ../crawler/data/toscrape/toscrape-1.index

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f settest
	rm -f core
	rm -f indexer
	rm -rf indextest
