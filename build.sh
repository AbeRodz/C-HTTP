#!/bin/bash

# Create build directory and go into it
mkdir -p build
cd build

# Run cmake and build
cmake .. || exit 1
make || exit 1

# Optional: run executable
if [ "$1" == "-r" ]; then
    echo -e "\nRunning Server..."
    ./main
fi
