#!/bin/bash
g++ -o hex hex.cpp `pkg-config --libs --cflags atom-0.2`
