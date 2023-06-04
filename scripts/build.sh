#!/usr/bin/env bash

cd ..
cmake -B build
cd build/
cmake --build .
cd ..
