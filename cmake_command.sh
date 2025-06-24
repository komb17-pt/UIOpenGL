#!/bin/bash


# Check if VCPKG_HOME is provided as command line argument
if [ $# -eq 1 ]; then
    VCPKG_HOME="$1"
else
    echo "Error: VCPKG_HOME argument is required"
    echo "Usage: $0 <VCPKG_HOME_PATH>"
    echo "Example: $0 /Users/vcpkg"
    exit 1
fi

cmake -DCMAKE_TOOLCHAIN_FILE=$VCPKG_HOME/vcpkg/scripts/buildsystems/vcpkg.cmake ..
