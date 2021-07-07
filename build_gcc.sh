# Can be compiled using simple compile commands
mkdir build_gcc
g++ -o build_gcc/inject src/inject.cpp src/common.cpp -fpermissive
g++ -o build_gcc/deinject src/deinject.cpp src/common.cpp -fpermissive
