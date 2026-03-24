#!/bin/bash
mkdir -p build
cd build
cmake ..
make
if [ $? -eq 0 ]; then
    ./Loro
else
    echo "Error: Compilation failed."
fi
