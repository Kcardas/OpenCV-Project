#!/bin/bash

g++ Testing\ Webcam.cpp -o OpenCVCode `pkg-config -cflags -libs opencv4`

echo "Compiled Succesfully"

