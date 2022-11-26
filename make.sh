#!/usr/bin/env bash

mkdir -p out/build &> /dev/null
cmake -S .  -B out/build
