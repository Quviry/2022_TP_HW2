

.PHONY: all build test rebuild clean

all: clean build test 



build: 
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	cmake --build build

test: build 
	cd ./build/tests && ctest --rerun-failed --output-on-failure

clean:
	rm -rf build

format:
	clang-format -i  ./src/* ./include/* ./tests/*.cpp --style=file

lint:
	clang-tidy  ./src/* ./include/* ./tests/*.cpp -header-filter=-*  --p=file -- -Iinclude/ -p build

memleak:
	valgrind --tool=memcheck --leak-check=yes ./build/tests/MatrixCalculator_unittest
