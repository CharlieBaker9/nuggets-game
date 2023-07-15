# Makefile for 'crawler' module
#
# Charlie Baker, April 2023

OBJS = crawler.o ../libcs50/webpage.o ../libcs50/bag.o ../common/pagedir.o
LIBS = ../libcs50/libcs50-given.a
L = ../libcs50

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make

crawler: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Dependencies: object files
crawler.o: ../libcs50/webpage.h ../libcs50/bag.h ../libcs50/libcs50-given.a ../common/pagedir.h ../libcs50/hashtable.h

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: test valgrind clean

# run test script
test: crawlertesting.sh
	./crawlertesting.sh 

# run valgrind with test script
valgrind:
	$(VALGRIND) mkdir data
	$(VALGRIND) mkdir data/letters
	$(VALGRIND) mkdir data/letters/depth0
	$(VALGRIND) ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ data/letters/depth0 0

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f settest
	rm -f core
	rm -f crawler
	rm -rf data
