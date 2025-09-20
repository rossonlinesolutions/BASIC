all:
	cmake -S . -B build
	cmake --build build

test:
	cd build && ctest --output-on-failure

clean:
	rm -rf build

.PHONY: all test clean
