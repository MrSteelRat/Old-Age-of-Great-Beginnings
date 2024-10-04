#!/bin/bash

# Create a directory for build
mkdir -p build

# Navigate to the build directory
cd build

# Generate Makefile using CMake
cmake ..

# Build the project
make -j$((`nproc`+1))
