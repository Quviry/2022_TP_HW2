

.PHONY: all build test rebuild clean

all: clean build test 



build: 
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	cmake --build build

test: build 
	cd ./build/tests && ctest 

clean:
	rm -rf build

format:
	clang-format -i  ./src/* ./include/*  --style=file

lint:
	clang-tidy  ./src/* ./include/* -header-filter=-*  --p=file -- -I/home/runner/work/2022_TP_HW2/2022_TP_HW2/include/ -p build

memleak:
	valgrind --tool=memcheck --leak-check=yes ./build/MatrixCalculator
