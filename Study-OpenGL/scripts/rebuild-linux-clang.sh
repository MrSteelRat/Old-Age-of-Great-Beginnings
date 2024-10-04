#!/bin/bash

# Fail on any error.
set -e

# Move to root of project.
cd "$(cd -P "$(dirname "$0")"/.. && pwd)"

# Remove cmake files that aren't required.
find -name CMakeCache.txt -o \
     -name CMakeFiles -o \
     -name CMakeScripts -o \
     -name cmake_install.cmake | xargs rm -rf

export CXX=${CXX:-"clang++-16"}

cmake -G Ninja -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --clean-first
