#!/bin/bash

echo "Starting CMake Build and making (aka Baking)"

BUILD_DIR="_build/"

# cd $BUILD_DIR
# cmake3 ..
# mv Makefile ../
# cd ..
# make

cmake3 .
make