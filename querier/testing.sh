#!/bin/bash
#
# Querier Testing
#
# Charlie Baker
# 13 May 2023
# Bash script which tests our querier.c implementation
#

echo ----------- querier tests that all have syntax errors ----------- 
./querier ~/cs50-dev/shared/tse/output/toscrape-2 ~/cs50-dev/shared/tse/output/toscrape-2.index < testInput1

echo ----------- querier tests using fuzzquery inputs ----------- 
./querier ~/cs50-dev/shared/tse/output/toscrape-2 ~/cs50-dev/shared/tse/output/toscrape-2.index < testInput2

echo ----------- querier tests using valid inputs ----------- 
./querier ~/cs50-dev/shared/tse/output/toscrape-2 ~/cs50-dev/shared/tse/output/toscrape-2.index < testInput3