#!/bin/bash

# Fail on any error.
set -e

# Move to root of project.
cd "$(cd -P "$(dirname "$0")"/.. && pwd)"

export PATH="/usr/lib/llvm-16/bin${PATH:+:${PATH}}"
export LD_LIBRARY_PATH="/usr/lib/llvm-16/lib${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}"

find src -name '*.h' -exec clang-format -i {} \;
find src -name '*.cpp' -exec clang-format -i {} \;
