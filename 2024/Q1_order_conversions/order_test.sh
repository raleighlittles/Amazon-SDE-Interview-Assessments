#!/usr/bin/env bash

set -e

# Build executable
cmake -S . -B build && cmake --build build

# Run the executable and pass in the input file to test with
./build/orderConversions < sample_input.txt > output.txt

diff output.txt expected_output.txt
error=$?

if [ $error -eq 0 ]; then
    echo "Q1 order conversions test passed! OK"
else
    echo "Error! Order conversions test failed, does not match expected output!"
fi