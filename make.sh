#!/usr/bin/env bash

mkdir -p out/build &> /dev/null
cmake -S .  -B out/build
cmake --build out/build 
ln -s out/build/MyString MyString &>/dev/null
