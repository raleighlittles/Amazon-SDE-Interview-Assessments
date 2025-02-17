#!/usr/bin/env bash

set -e

# Build executable
cmake -S . -B build && cmake --build build

# Execute and save output to a text file
./build/FizzBuzz > output.txt

diff output.txt sample_output.txt
error=$?

if [ $error -eq 0 ]; then
    echo "Fizzbuzz test passed! OK"
else
    echo "Error! FizzBuzz test failed, does not match expected output!"
fi