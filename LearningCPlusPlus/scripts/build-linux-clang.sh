#!/bin/bash

# Fail on any error.
set -e

# Move to root of project.
cd "$(cd -P "$(dirname "$0")"/.. && pwd)"

export CC=${CC:-"clang-13"}

cmake -G Ninja -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
