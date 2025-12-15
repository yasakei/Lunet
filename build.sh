#!/bin/bash

# Build script for Lunet on Linux
BUILD_DIR="build"

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Change to build directory and run cmake
cd "$BUILD_DIR"
cmake ..
make

echo "Build completed. Run with: ./build/Lunet <filename>"