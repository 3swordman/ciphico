mkdir ./build
cd ./build
cmake ..
cmake --build . --config Release
cmake --install .
echo use "./ciphico [the phico source file] to begin"