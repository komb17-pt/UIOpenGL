#!/bin/bash

# Usage:
#   ./build_and_run.sh         # Builds and run
#   ./build_and_run.sh clean   # Removes build dir


BUILD_DIR="build"
EXECUTABLE_NAME="uiopengl"
TOOLCHAIN_FILE="/Users/pt/Code/vcpkg/scripts/buildsystems/vcpkg.cmake"

# clean
if [ "$1" = "clean" ]; then
    echo "Cleaning build directory: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
    if [ $? -eq 0 ]; then
        echo "Build directory removed "
    else
        echo "Failed to remove build "
    fi
    exit 0
fi

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || { echo "Failed to enter build directory"; exit 1; }

# Run CMake
cmake -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE" ..
if [ $? -ne 0 ]; then
    echo "CMake failed"
    exit 1
fi

# Build
cmake --build .
if [ $? -ne 0 ]; then
    echo "Build failed "
    exit 1
fi

# Run
./"$EXECUTABLE_NAME"
if [ $? -ne 0 ]; then
    echo "Executable failed "
    exit 1
fi

