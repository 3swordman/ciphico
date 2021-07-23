@echo off
mkdir build
cd build
cmake ..
cmake --build .
cmake --install .
echo use "ciphico [the phico source file] to begin"