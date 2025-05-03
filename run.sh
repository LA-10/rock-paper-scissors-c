#!/bin/bash

mkdir -p build && cd build
cmake ..
make
./rock-paper-scissors-c
