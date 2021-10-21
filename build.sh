#!/usr/bin/env bash

rm -rf build
mkdir build

clang -g -Wall -O1 src/**.c -o build/main