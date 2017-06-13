#!/bin/bash
# Run this file via bash command as follows:
# bash scripts/runAllTests.sh

# this will produce test case output stored in the output folder

mkdir -p output
for i in `seq 1 7`
do
    echo -n "Running test case ${i}"
    src/CSCI8150 test/test${i}.txt > output/test${i}_results.txt
    echo " -> output/test${i}_results.txt"
done
