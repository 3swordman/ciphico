@echo off
mkdir build
cd build
cmake ..
cmake --build .
echo use "ciphico [the phico source file] to begin"