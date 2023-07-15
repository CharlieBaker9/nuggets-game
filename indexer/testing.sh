#!/bin/bash
#
# Indexer Testing
#
# Charlie Baker
# 3 May 2023
# Bash script which tests our indexer.c implementation
# Uses indextest.c as a helper function
#

echo ----------- indexer tests that should fail ----------- 

echo Output from zero arguments -- too few
./indexer
echo

echo Output from 1 arguments -- too few
./indexer ../crawler/data/letters/depth10
echo

echo Output from 3 arguments -- too many
./indexer ../crawler/data/letters/depth10 ../crawler/data/letters/depth10.index ../extra
echo

echo Output from 4 arguments -- too many
./indexer ../crawler/data/letters/depth10 ../crawler/data/letters/depth10.index ../extra ../extra2
echo

echo Output from invalid pageDirectory -- non-existent path 
./indexer ../crawler/data/letters/invalid ../crawler/data/letters/depth10.index
echo

echo Output from invalid pageDirectory -- not a crawler directory
./indexer ../common ../common.index
echo

echo Output from invalid indexFile -- non-existent path
./indexer ../crawler/data/letters/invalid ../crawler/empty/depth10.index
echo

echo ----------- indextest runs that should fail ----------- 

echo Output from zero arguments -- too few
./indextest
echo

echo Output from 1 arguments -- too few
./indextest ../crawler/data/letters/depth10
echo

echo Output from 3 arguments -- too many
./indextest ../crawler/data/letters/depth10 justRight tooMuch
echo

echo ----------- running indextest and then comparing to validate index ----------- 

echo Output from running index test on toscrape-1 and then comparing
./indextest ../../shared/tse/indices/toscrape-1.ndx ../crawler/data/toscrape/indextest-toscrape-1.index
~/cs50-dev/shared/tse/indexcmp ../../shared/tse/indices/toscrape-1.ndx ../crawler/data/toscrape/indextest-toscrape-1.index
echo

echo Output from running index test on wikipedia_2 and then comparing
./indextest ../../shared/tse/indices/wikipedia_2.ndx ../crawler/data/wikipedia/indextest-wikipedia-2.index
~/cs50-dev/shared/tse/indexcmp ../../shared/tse/indices/wikipedia_2.ndx ../crawler/data/wikipedia/indextest-wikipedia-2.index
echo

echo ----------- tests that should run correctly ----------- 

echo output from running indexer on ../crawler/data/letters/depth0
./indexer ../crawler/data/letters/depth0 ../crawler/data/letters/depth0.index
echo

echo output from running indexer on ../crawler/data/letters/depth10
./indexer ../crawler/data/letters/depth10 ../crawler/data/letters/depth10.index
echo

echo output from running indexer on ../crawler/data/toscrape/depth0
./indexer ../crawler/data/toscrape/depth0 ../crawler/data/toscrape/depth0.index
echo

echo output from running indexer on ../crawler/data/toscrape/depth1
./indexer ../crawler/data/toscrape/depth1 ../crawler/data/toscrape/depth1.index
echo

echo output from running indexer on ../crawler/data/wikipedia/depth0
./indexer ../crawler/data/wikipedia/depth0 ../crawler/data/wikipedia/depth0.index
echo

echo output from running indexer on ../crawler/data/wikipedia/depth1
./indexer ../crawler/data/wikipedia/depth1 ../crawler/data/wikipedia/depth1.index
echo

echo ----------- running valgrind ----------- 

echo Output from running make valgrind indexer
make valgrind
echo
