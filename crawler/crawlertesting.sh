#!/bin/bash
#
# Crawler Testing
#
# Charlie Baker
# 28 April 2023
# Bash script which tests our crawler.c implementation
#

mkdir data
mkdir data/letters
mkdir data/letters/depth0
mkdir data/letters/depth10
mkdir data/toscrape
mkdir data/toscrape/depth0
mkdir data/toscrape/depth1
mkdir data/wikipedia
mkdir data/wikipedia/depth0
mkdir data/wikipedia/depth1

echo ----------- tests that should fail ----------- 

echo Output from zero arguments -- too few
./crawler
echo

echo Output from 1 arguments -- too few
./crawler http://cs50tse.cs.dartmouth.edu/tse/
echo

echo Output from 2 arguments -- too few
./crawler http://cs50tse.cs.dartmouth.edu/tse/ data/letters
echo

echo Output from 4 arguments -- too many
./crawler http://cs50tse.cs.dartmouth.edu/tse/ data/letters 0 tooMany
echo

echo Output from maxDepth of 12 -- to large
./crawler http://cs50tse.cs.dartmouth.edu/tse/ data/letters 12
echo

echo ----------- letters test runs ----------- 

echo Output from letters with depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ data/letters/depth0 0

echo Output from letters with depth 10
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ data/letters/depth10 10
echo

echo ----------- toscrape test runs ----------- 

echo Output from toscrape with depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ data/toscrape/depth0 0

echo Output from toscrape with depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ data/toscrape/depth1 1
echo

echo ----------- wikipedia test runs ----------- 

echo Output from wikipedia with depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ data/wikipedia/depth0 0

echo Output from wikipedia with depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ data/wikipedia/depth1 1


