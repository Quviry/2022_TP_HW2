

.PHONY: all build test rebuild clean

all: clean build test 



build: 
	cmake -S . -B build
	cmake --build build

test: build 
	cd ./build && ctest 

clean:
	rm -rf build

format:
	clang-format -i  ./src/* ./include/*  --style=file

lint:
	clang-tidy  ./src/* ./include/*  --p=file -- -Iinclude/

memleak:
	valgrind --tool=memcheck --leak-check=yes ./build/MatrixCalculator