

.PHONY: all build test rebuild clean

all: clean build test 



build: 
	cmake -S . -B build
	cmake --build build

test: build 
	cd ./build && ctest 

clean:
	rm -rf build