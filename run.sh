#!/bin/bash

set -e  # Stop if any command fails

make clean
make
./game
