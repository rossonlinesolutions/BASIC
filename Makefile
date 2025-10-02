all:
	cmake -S . -B build
	cmake --build build

test:
	cd build && ctest --output-on-failure

clean:
	rm -rf build

stats:
	@find . -regextype posix-egrep -regex ".*\.([ch]pp|[ch])" -not -path "./build/*" | xargs wc -l | sort -n

.PHONY: all test clean stats
