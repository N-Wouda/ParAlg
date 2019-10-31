#!/usr/bin/env bash

# Fixes all non-conforming source and header files in the cat/ directory.
find cat/ -iname "*.h" -o -iname "*.c" | xargs clang-format -i

# Get all files modified by clang-format.
dirty=$(git ls-files --modified)

if [[ $dirty ]];
then
  echo "Files with unexpected source code formatting:"
  echo $dirty
fi
