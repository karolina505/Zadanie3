
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

all: main

main: main.cpp arraylist.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

test: main
	./main

clean:
	rm -f main

.PHONY: all test clean
