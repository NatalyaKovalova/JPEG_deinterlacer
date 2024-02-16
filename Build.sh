mkdir -p build

cd build

cmake ..
make

cd ..

# Run the executable
./build/JPEGDeinterlacer "$@"