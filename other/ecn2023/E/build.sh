#!/bin/bash

# export CXX=/usr/bin/clang-17
export CMAKE_BUILD_TYPE=Debug

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_CXX_COMPILER=$CXX -B build .

rm -r build/

cmake -B build

cd build && make
