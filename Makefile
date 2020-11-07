CXX = g++
CPPFLAGS = -Wall -Wextra -Wno-unused-parameter -Iinclude/ -g -Og

all: main

main: src/main.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^