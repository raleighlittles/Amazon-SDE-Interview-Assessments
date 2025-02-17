#!/usr/bin/env bash

set -e

# Build executable
cmake -S . -B build && cmake --build build

# Run the executable and pass in the input file to test with
./build/startingInABit < sample_input_1.txt > output.txt

diff output.txt expected_output_1.txt
error=$?

if [ $error -eq 0 ]; then
    echo "Q2 'starting in a bit' test case #1 passed! OK"
else
    echo "Error! Q2 test(s) failed, does not match expected output!"
fi